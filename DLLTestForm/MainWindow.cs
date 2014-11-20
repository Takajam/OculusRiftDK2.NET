using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.IO;

using OpenTK;
using OpenTK.Graphics.OpenGL;

using OculusDK2NET;


namespace DLLTestForm
{
    public partial class MainWindow : Form
    {
        //Oculus DK2 レンダリングに必要な変数
        private HmdDesc hmd;
        private bool isHmdInitialized = false;
        private EyeRenderDesc[] eyeRenderDesc;
        private Recti[] eyeRenderViewport;

        //フレームバッファ
        private static uint frameBufferId;
        private static uint textureId;
        private static uint depthBufferId;

        //Clienet Distortion Rendering用のメッシュ
        private int[] meshVBs;
        private int[] meshIBs;
        private int[] meshVAs;
        private Vector2f[][] uvScaleOffset;
        private int[] meshIndexCount;

        //シェーダー
        private static int shaderProgram;
        private const string vertexShaderFileName = "./Shader/vertex_shader.vert";
        private const string fragmentShaderFileName = "./Shader/fragment_shader.frag";
        private static string vertexShaderCode;
        private static string fragmentShaderCode;

        private bool isFullscreen = false;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();
        }

        /// <summary>
        /// この関数がMain()から毎フレーム呼び出される．
        /// </summary>
        public void MainLoop()
        {
            this.Invalidate();  //実際の処理はOnPaintメソッドに書く
        }

        /// <summary>
        /// シーンを描画してglControlを更新する．
        /// </summary>
        /// <param name="e"></param>
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            if (isHmdInitialized)
            {
                //シーンをオフスクリーンレンダリングする
                Posef[] headPose = new Posef[2];

                FrameTiming frameTiming = OvrHmd.BeginFrame(hmd, 0);

                GL.Ext.BindFramebuffer(FramebufferTarget.FramebufferExt, frameBufferId);

                GL.ClearColor(Color.SkyBlue);
                GL.ClearDepth(1.0);
                GL.Enable(EnableCap.DepthTest);

                GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
                
                for (var eyeIndex = 0; eyeIndex < 2; eyeIndex++)
                {
                    EyeType eye = this.hmd.EyeRenderOrder[eyeIndex];
                    headPose[(int)eye] = OvrHmd.GetHmdPosePerEye(this.hmd, eye);

                    GL.Viewport(this.eyeRenderViewport[(int)eye].Pos.x, this.eyeRenderViewport[(int)eye].Pos.y, this.eyeRenderViewport[(int)eye].Size.w, this.eyeRenderViewport[(int)eye].Size.h);

                    Matrix4f ovrProj = OvrHmd.Matrix4f_Projection(this.eyeRenderDesc[(int)eye].Fov, 0.01f, 100.0f, true);
                    Matrix4 proj = new Matrix4(
                        ovrProj.M[0][0], ovrProj.M[1][0], ovrProj.M[2][0], ovrProj.M[3][0],
                        ovrProj.M[0][1], ovrProj.M[1][1], ovrProj.M[2][1], ovrProj.M[3][1],
                        ovrProj.M[0][2], ovrProj.M[1][2], ovrProj.M[2][2], ovrProj.M[3][2],
                        ovrProj.M[0][3], ovrProj.M[1][3], ovrProj.M[2][3], ovrProj.M[3][3]
                        );      //OpenTKとOculusでは行列が転置するので注意
                    GL.MatrixMode(MatrixMode.Projection);
                    GL.LoadMatrix(ref proj);

                    Quatf orientation = headPose[(int)eye].Orientation;

                    Matrix4 view = Matrix4.Identity;
                    view = Matrix4.Mult(view, Matrix4.CreateTranslation(this.eyeRenderDesc[(int)eye].HmdToEyeViewOffset.x, this.eyeRenderDesc[(int)eye].HmdToEyeViewOffset.y, this.eyeRenderDesc[(int)eye].HmdToEyeViewOffset.z));
                    view = Matrix4.Mult(view, Matrix4.CreateTranslation(0.0f, 0.0f, -4.0f));
                    view = Matrix4.Mult(view, Matrix4.CreateFromQuaternion(new Quaternion(orientation.Inverted().x, orientation.Inverted().y, orientation.Inverted().z, orientation.Inverted().w)));
                    GL.MatrixMode(MatrixMode.Modelview);
                    GL.LoadMatrix(ref view);

                    DrawScene(); 
                }

                GL.Disable(EnableCap.DepthTest);
                GL.Disable(EnableCap.CullFace);

                OvrHmd.WaitTillTime(frameTiming.TimewarpPointSeconds);

                //Client Distortion Rendering
                GL.Ext.BindFramebuffer(FramebufferTarget.FramebufferExt, 0);

                GL.UseProgram(shaderProgram);

                GL.ClearColor(Color.Black);
                GL.Disable(EnableCap.DepthTest);
                GL.Clear(ClearBufferMask.ColorBufferBit);

                GL.Viewport(0, 0, hmd.Resolution.w, hmd.Resolution.h);

                GL.Enable(EnableCap.Texture2D);
                GL.BindTexture(TextureTarget.Texture2D, textureId);
                GL.Uniform1(GL.GetUniformLocation(shaderProgram, "Texture0"), 0);

                for (var eyeNum = 0; eyeNum < 2; eyeNum++)
                {
                    GL.Uniform2(GL.GetUniformLocation(shaderProgram, "EyeToSourceUVscale"), uvScaleOffset[eyeNum][0].x, -uvScaleOffset[eyeNum][0].y);       //OpenGLは左下原点
                    GL.Uniform2(GL.GetUniformLocation(shaderProgram, "EyeToSourceUVoffset"), uvScaleOffset[eyeNum][1].x, 1 - uvScaleOffset[eyeNum][1].y);   //OpenGLは左下原点

                    Matrix4f[] timeWarpMatrices = new Matrix4f[2];
                    OvrHmd.GetEyeTimewarpMatrices(hmd, (EyeType)eyeNum, headPose[eyeNum], timeWarpMatrices);

                    Matrix4 m0 = new Matrix4(
                        timeWarpMatrices[0].M[0][0], timeWarpMatrices[0].M[1][0], timeWarpMatrices[0].M[2][0], timeWarpMatrices[0].M[3][0],
                        timeWarpMatrices[0].M[0][1], timeWarpMatrices[0].M[1][1], timeWarpMatrices[0].M[2][1], timeWarpMatrices[0].M[3][1],
                        timeWarpMatrices[0].M[0][2], timeWarpMatrices[0].M[1][2], timeWarpMatrices[0].M[2][2], timeWarpMatrices[0].M[3][2],
                        timeWarpMatrices[0].M[0][3], timeWarpMatrices[0].M[1][3], timeWarpMatrices[0].M[2][3], timeWarpMatrices[0].M[3][3]
                        );

                    Matrix4 m1 = new Matrix4(
                        timeWarpMatrices[1].M[0][0], timeWarpMatrices[1].M[1][0], timeWarpMatrices[1].M[2][0], timeWarpMatrices[1].M[3][0],
                        timeWarpMatrices[1].M[0][1], timeWarpMatrices[1].M[1][1], timeWarpMatrices[1].M[2][1], timeWarpMatrices[1].M[3][1],
                        timeWarpMatrices[1].M[0][2], timeWarpMatrices[1].M[1][2], timeWarpMatrices[1].M[2][2], timeWarpMatrices[1].M[3][2],
                        timeWarpMatrices[1].M[0][3], timeWarpMatrices[1].M[1][3], timeWarpMatrices[1].M[2][3], timeWarpMatrices[1].M[3][3]
                        );

                    GL.UniformMatrix4(GL.GetUniformLocation(shaderProgram, "EyeRotationStart"), false, ref m0);
                    GL.UniformMatrix4(GL.GetUniformLocation(shaderProgram, "EyeRotationEnd"), false, ref m1);

                    GL.BindVertexArray(meshVAs[eyeNum]);
                    GL.BindBuffer(BufferTarget.ArrayBuffer, meshVBs[eyeNum]);
                    GL.BindBuffer(BufferTarget.ElementArrayBuffer, meshIBs[eyeNum]);
                    GL.DrawElements(BeginMode.Triangles, meshIndexCount[eyeNum], DrawElementsType.UnsignedInt, 0);
                    GL.BindVertexArray(0);
                    GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
                    GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
                }

                GL.Disable(EnableCap.Texture2D);
                GL.Enable(EnableCap.DepthTest);

                GL.UseProgram(0);
                
                glControlDisplayPanel.SwapBuffers();

                OvrHmd.EndFrameTiming(hmd);
            }
        }
        
        /// <summary>
        /// 初期化処理．
        /// MainWindow_Loadで書くとglControlを初期化するときに失敗する．
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainWindow_Shown(object sender, EventArgs e)
        {
            //HMDを初期化
            OvrHmd.Initialize();

            if (OvrHmd.Detect() > 0)
            {
                hmd = OvrHmd.Create(0);
            }
            else
            {
                hmd = OvrHmd.CreateDebug(HmdType.DK2);
                MessageBox.Show("Oculus DK2が接続されていません");
            }

            if (hmd.Type != HmdType.DK2)
            {
                MessageBox.Show("接続されているデバイスはDK2ではありません");
            }

            //GLControlの初期化
            this.glControlDisplayPanel.Size = new Size(hmd.Resolution.w, hmd.Resolution.h);
            this.glControlDisplayPanel.Location = new Point(0, 0);
            this.glControlDisplayPanel.MakeCurrent();
            this.ClientSize = this.glControlDisplayPanel.Size;

            //Debug: hmdの内容を書き出す
            #region
            if (hmd != null)
            {
                Debug.WriteLine("Type: {0}" + hmd.Type.ToString());
                Debug.WriteLine("ProductName: " + hmd.ProductName);
                Debug.WriteLine("Manufacturer: " + hmd.Manufacturer);
                Debug.WriteLine("Vendor ID: " + hmd.VendorId.ToString());
                Debug.WriteLine("Product ID: " + hmd.ProductId.ToString());
                Debug.WriteLine("Serial Number: " + hmd.SerialNumber);
                Debug.WriteLine("Firmware Major: " + hmd.FirmwareMajor.ToString());
                Debug.WriteLine("Firmware Minor: " + hmd.FirmwareMinor.ToString());
                Debug.WriteLine("");
                Debug.WriteLine("Camera Frustum Horizontal Fov In Radians: " + hmd.CameraFrustumHFovInRadians.ToString());
                Debug.WriteLine("Camera Frustum Virtical Fov In Radians: " + hmd.CameraFrustumVFovInRadians.ToString());
                Debug.WriteLine("Camera Frustum Near Z In Meters: " + hmd.CameraFrustumNearZInMeters.ToString());
                Debug.WriteLine("Camera Frustum Far Z In Meters: " + hmd.CameraFrustumFarZInMeters.ToString());
                Debug.WriteLine("");
                Debug.WriteLine("Hmd Caps: " + hmd.HmdCaps.ToString());
                Debug.WriteLine("Tracking Caps: " + hmd.TrackingCaps.ToString());
                Debug.WriteLine("Distortion Caps: " + hmd.DistortionCaps.ToString());
                Debug.WriteLine("");
                Debug.WriteLine("Resolution: " + hmd.Resolution.w.ToString() + " * " + hmd.Resolution.h.ToString());
                Debug.WriteLine("Windows Pos: " + hmd.WindowsPos.x.ToString() + ", " + hmd.WindowsPos.y.ToString());
                Debug.WriteLine("");
                Debug.WriteLine("Default Eye Fov: " + hmd.DefaultEyeFov[0].UpTan.ToString() + ", " + hmd.DefaultEyeFov[1].UpTan.ToString());
                Debug.WriteLine("Max Eye Fov: " + hmd.MaxEyeFov[0].UpTan.ToString() + ", " + hmd.MaxEyeFov[1].UpTan.ToString());
                Debug.WriteLine("");
                Debug.WriteLine("Eye Render Order: " + hmd.EyeRenderOrder[0].ToString() + ", " + hmd.EyeRenderOrder[1].ToString());
                Debug.WriteLine("");
                Debug.WriteLine("Display Device Name: " + hmd.DisplayDeviceName);
                Debug.WriteLine("Display ID: " + hmd.DisplayId.ToString());
            }
            #endregion

            OvrHmd.SetEnabledCaps(hmd, HmdCaps.LowPersistence | HmdCaps.DynamicPrediction);

            //トラッキングの初期化
            OvrHmd.ConfigureTracking(hmd, TrackingCaps.Orientation | TrackingCaps.MagYawCorrection | TrackingCaps.Position, 0);
            OvrHmd.RecenterPose(hmd);
            
            //OpenGL：レンダリングの初期化
            //シェーダーの読み込み
            int vertexShader = GL.CreateShader(ShaderType.VertexShader);
            int fragmentShader = GL.CreateShader(ShaderType.FragmentShader);

            using (StreamReader vs = new StreamReader(vertexShaderFileName, System.Text.Encoding.UTF8))
            {
                vertexShaderCode = vs.ReadToEnd();
            }

            using (StreamReader fs = new StreamReader(fragmentShaderFileName, System.Text.Encoding.UTF8))
            {
                fragmentShaderCode = fs.ReadToEnd();
            }

            string info;
            int status_code;

            GL.ShaderSource(vertexShader, vertexShaderCode);
            GL.CompileShader(vertexShader);
            GL.GetShaderInfoLog(vertexShader, out info);
            GL.GetShader(vertexShader, ShaderParameter.CompileStatus, out status_code);
            if(status_code != 1)
            {
                throw new ApplicationException(info);
            }

            GL.ShaderSource(fragmentShader, fragmentShaderCode);
            GL.CompileShader(fragmentShader);
            GL.GetShaderInfoLog(fragmentShader, out info);
            GL.GetShader(fragmentShader, ShaderParameter.CompileStatus, out status_code);
            if (status_code != 1)
            {
                throw new ApplicationException(info);
            }

            shaderProgram = GL.CreateProgram();
            GL.AttachShader(shaderProgram, vertexShader);
            GL.AttachShader(shaderProgram, fragmentShader);
            GL.LinkProgram(shaderProgram);


            //レンダーターゲットの初期化
            Sizei recommendedTex0Size = OvrHmd.GetFovTextureSize(hmd, EyeType.Left, hmd.DefaultEyeFov[0], 1.0f);
            Sizei recommendedTex1Size = OvrHmd.GetFovTextureSize(hmd, EyeType.Right, hmd.DefaultEyeFov[1], 1.0f);
            Sizei renderTargetSize = new Sizei();
            renderTargetSize.w = recommendedTex0Size.w + recommendedTex1Size.w;
            renderTargetSize.h = Math.Max(recommendedTex0Size.h, recommendedTex1Size.h);
                       
            //フレームバッファの初期化
            GL.GenTextures(1, out textureId);
            GL.BindTexture(TextureTarget.Texture2D, textureId);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)TextureWrapMode.ClampToEdge);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)TextureWrapMode.ClampToEdge);
            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, renderTargetSize.w, renderTargetSize.h, 0, PixelFormat.Rgba, PixelType.UnsignedByte, IntPtr.Zero);

            GL.Ext.GenRenderbuffers(1, out depthBufferId);
            GL.Ext.BindRenderbuffer(RenderbufferTarget.RenderbufferExt, depthBufferId);
            GL.Ext.RenderbufferStorage(RenderbufferTarget.RenderbufferExt, RenderbufferStorage.DepthComponent24, renderTargetSize.w, renderTargetSize.h);

            GL.Ext.GenFramebuffers(1, out frameBufferId);
            GL.Ext.BindFramebuffer(FramebufferTarget.FramebufferExt, frameBufferId);
            GL.Ext.FramebufferTexture2D(FramebufferTarget.FramebufferExt, FramebufferAttachment.ColorAttachment0Ext, TextureTarget.Texture2D, textureId, 0);
            GL.Ext.FramebufferRenderbuffer(FramebufferTarget.FramebufferExt, FramebufferAttachment.DepthAttachmentExt, RenderbufferTarget.RenderbufferExt, depthBufferId);
            
            if (GL.CheckFramebufferStatus(FramebufferTarget.Framebuffer) != FramebufferErrorCode.FramebufferComplete)
            {
                MessageBox.Show("imcomplete framebuffer!");
            }

            GL.BindFramebuffer(FramebufferTarget.Framebuffer, 0);

            //ビューポートの初期化
            FovPort[] eyeFov = new FovPort[2];
            eyeFov[0] = hmd.DefaultEyeFov[0];
            eyeFov[1] = hmd.DefaultEyeFov[1];

            this.eyeRenderViewport = new Recti[2];
            this.eyeRenderViewport[0] = new Recti(new Vector2i(0, 0), new Sizei(renderTargetSize.w / 2, renderTargetSize.h));
            this.eyeRenderViewport[1] = new Recti(new Vector2i((renderTargetSize.w + 1) / 2, 0), new Sizei(renderTargetSize.w / 2, renderTargetSize.h));

            this.eyeRenderDesc = new EyeRenderDesc[2];
            this.eyeRenderDesc[0] = new EyeRenderDesc();
            this.eyeRenderDesc[1] = new EyeRenderDesc();

            //Clienet Distortion Rendering：メッシュを初期化
            this.meshVBs = new int[2];
            this.meshIBs = new int[2];
            this.meshVAs = new int[2];
            this.meshIndexCount = new int[2];

            this.uvScaleOffset = new Vector2f[2][];
            this.uvScaleOffset[0] = new Vector2f[2];
            this.uvScaleOffset[1] = new Vector2f[2];
            
            for (var eyeNum = 0; eyeNum < 2; eyeNum++)
            {
                DistortionMesh meshData;
                OvrHmd.CreateDistortionMesh(hmd, (EyeType)eyeNum, eyeFov[eyeNum], DistortionCaps.Chromatic | DistortionCaps.TimeWarp, out meshData);

                int vertexSize = 2 + 1 + 1 + 2 + 2 + 2;
                float[] vertexData = new float[vertexSize * meshData.VertexCount];
                DistortionVertex[] meshArray = meshData.VertexData.ToArray();

                for (var v = 0; v < meshData.VertexCount; v++)
                {
                    vertexData[v * vertexSize + 0] = meshArray[v].ScreenPosNDC.x;
                    vertexData[v * vertexSize + 1] = meshArray[v].ScreenPosNDC.y;
                    vertexData[v * vertexSize + 2] = meshArray[v].TimeWarpFactor;
                    vertexData[v * vertexSize + 3] = meshArray[v].VignetteFactor;
                    vertexData[v * vertexSize + 4] = meshArray[v].TanEyeAnglesR.x;
                    vertexData[v * vertexSize + 5] = meshArray[v].TanEyeAnglesR.y;
                    vertexData[v * vertexSize + 6] = meshArray[v].TanEyeAnglesG.x;
                    vertexData[v * vertexSize + 7] = meshArray[v].TanEyeAnglesG.y;
                    vertexData[v * vertexSize + 8] = meshArray[v].TanEyeAnglesB.x;
                    vertexData[v * vertexSize + 9] = meshArray[v].TanEyeAnglesB.y;
                }

                GL.GenBuffers(1, out meshVBs[eyeNum]);
                GL.BindBuffer(BufferTarget.ArrayBuffer, meshVBs[eyeNum]);
                GL.BufferData(BufferTarget.ArrayBuffer, new IntPtr(vertexData.Length * sizeof(float)), vertexData, BufferUsageHint.StaticDraw);

                GL.BindBuffer(BufferTarget.ArrayBuffer, 0);

                meshIndexCount[eyeNum] = (int)meshData.IndexCount;
                ushort[] indexData = meshData.IndexData.ToArray();
                uint[] indicesData = new uint[meshData.IndexCount];
                for (var i = 0; i < meshData.IndexCount; i++)
                {
                    indicesData[i] = (uint)indexData[i];
                }

                GL.GenBuffers(1, out meshIBs[eyeNum]);
                GL.BindBuffer(BufferTarget.ElementArrayBuffer, meshIBs[eyeNum]);
                GL.BufferData(BufferTarget.ElementArrayBuffer, new IntPtr(meshData.IndexCount * sizeof(uint)), indicesData, BufferUsageHint.StaticDraw);

                GL.BindBuffer(BufferTarget.ArrayBuffer, 0);

                GL.BindBuffer(BufferTarget.ArrayBuffer, meshVBs[eyeNum]);

                GL.GenVertexArrays(1, out meshVAs[eyeNum]);
                GL.BindVertexArray(meshVAs[eyeNum]);
                GL.BindBuffer(BufferTarget.ElementArrayBuffer, meshIBs[eyeNum]);

                for (int attrib = 0; attrib < 6; attrib++)
                {
                    GL.EnableVertexAttribArray(attrib);
                }
                int stride = 10 * sizeof(float);
                GL.VertexAttribPointer(0, 2, VertexAttribPointerType.Float, false, stride, 0);
                GL.VertexAttribPointer(1, 1, VertexAttribPointerType.Float, false, stride, 2 * sizeof(float));
                GL.VertexAttribPointer(2, 1, VertexAttribPointerType.Float, false, stride, (2 + 1) * sizeof(float));
                GL.VertexAttribPointer(3, 2, VertexAttribPointerType.Float, false, stride, (2 + 1 + 1) * sizeof(float));
                GL.VertexAttribPointer(4, 2, VertexAttribPointerType.Float, false, stride, (2 + 1 + 1 + 2) * sizeof(float));
                GL.VertexAttribPointer(5, 2, VertexAttribPointerType.Float, false, stride, (2 + 1 + 1 + 2 + 2) * sizeof(float));

                GL.BindVertexArray(0);

                GL.BindBuffer(BufferTarget.ArrayBuffer, 0);

                OvrHmd.DestroyDistortionMesh(ref meshData);

                eyeRenderDesc[eyeNum] = OvrHmd.GetRenderDesc(hmd, (EyeType)eyeNum, eyeFov[eyeNum]);

                OvrHmd.GetRenderScaleAndOffset(eyeFov[eyeNum], renderTargetSize, eyeRenderViewport[eyeNum], uvScaleOffset[eyeNum]);
            }

            this.isHmdInitialized = true;
        }

        /// <summary>
        /// 終了．
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            GL.Ext.DeleteFramebuffers(1, ref frameBufferId);
            GL.Ext.DeleteRenderbuffers(1, ref depthBufferId);
            GL.DeleteTextures(1, ref textureId);

            OvrHmd.Destroy(hmd);
            OvrHmd.Shutdown();
        }

        /// <summary>
        /// キーボード入力．
        /// R：ヘッドトラッキングをゼロセット．
        /// F：フルスクリーン切り替え
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainWindow_KeyDown(object sender, KeyEventArgs e)
        {
            switch(e.KeyCode)
            {
                case Keys.R:
                    //ヘッドトラッキング　ゼロセット
                    if(this.isHmdInitialized)
                    {
                        OvrHmd.RecenterPose(hmd);
                    }

                    break;

                case Keys.F:
                    //フルスクリーン
                    if (isFullscreen)
                    {
                        this.WindowState = FormWindowState.Normal;
                        this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;

                        isFullscreen = false;
                    }
                    else
                    {
                        this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
                        this.WindowState = FormWindowState.Maximized;

                        isFullscreen = true;
                    }

                    break;

            }
        }

        /// <summary>
        /// シーンのレンダリングはここに書く．
        /// サンプルなので板ポリゴンを表示するだけ．
        /// </summary>
        private void DrawScene()
        {
            GL.MatrixMode(MatrixMode.Modelview);
            GL.PushMatrix();
            GL.Begin(BeginMode.Polygon);
            GL.Color3(1.0f, 1.0f, 1.0f);
            GL.Vertex3(-1.0, -1.0, 0.0);
            GL.Vertex3(1.0, -1.0, 0.0);
            GL.Vertex3(1.0, 1.0, 0.0);
            GL.Vertex3(-1.0, 1.0, 0.0);
            GL.End();
            GL.PopMatrix();
        }
    }
}
