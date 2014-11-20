namespace DLLTestForm
{
    partial class MainWindow
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.glControlDisplayPanel = new OpenTK.GLControl();
            this.SuspendLayout();
            // 
            // glControlDisplayPanel
            // 
            this.glControlDisplayPanel.BackColor = System.Drawing.Color.Black;
            this.glControlDisplayPanel.Location = new System.Drawing.Point(0, 0);
            this.glControlDisplayPanel.Name = "glControlDisplayPanel";
            this.glControlDisplayPanel.Size = new System.Drawing.Size(1920, 1080);
            this.glControlDisplayPanel.TabIndex = 0;
            this.glControlDisplayPanel.VSync = false;
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.glControlDisplayPanel);
            this.KeyPreview = true;
            this.Name = "MainWindow";
            this.Text = "Oculus DK2 DLL Test";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainWindow_FormClosing);
            this.Shown += new System.EventHandler(this.MainWindow_Shown);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainWindow_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion

        private OpenTK.GLControl glControlDisplayPanel;

    }
}

