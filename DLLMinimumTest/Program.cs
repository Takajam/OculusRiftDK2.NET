using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using OculusDK2NET;

namespace DLLMinimumTest
{
    class Program
    {
        static void Main(string[] args)
        {
            HmdDesc hmd;

            OvrHmd.Initialize();

            if (OvrHmd.Detect() > 0)
            {
                hmd = OvrHmd.Create(0);
            }
            else
            {
                hmd = OvrHmd.CreateDebug(HmdType.DK2);
                Console.WriteLine("Oculus DK2が接続されていません");
            }

            if (hmd.Type != HmdType.DK2)
            {
                Console.WriteLine("接続されているデバイスはDK2ではありません");
            }

            if (hmd != null)
            {
                Console.WriteLine("Type: {0}" + hmd.Type.ToString());
                Console.WriteLine("ProductName: " + hmd.ProductName);
                Console.WriteLine("Manufacturer: " + hmd.Manufacturer);
                Console.WriteLine("Vendor ID: " + hmd.VendorId.ToString());
                Console.WriteLine("Product ID: " + hmd.ProductId.ToString());
                Console.WriteLine("Serial Number: " + hmd.SerialNumber);
                Console.WriteLine("Firmware Major: " + hmd.FirmwareMajor.ToString());
                Console.WriteLine("Firmware Minor: " + hmd.FirmwareMinor.ToString());
                Console.WriteLine("");
                Console.WriteLine("Camera Frustum Horizontal Fov In Radians: " + hmd.CameraFrustumHFovInRadians.ToString());
                Console.WriteLine("Camera Frustum Virtical Fov In Radians: " + hmd.CameraFrustumVFovInRadians.ToString());
                Console.WriteLine("Camera Frustum Near Z In Meters: " + hmd.CameraFrustumNearZInMeters.ToString());
                Console.WriteLine("Camera Frustum Far Z In Meters: " + hmd.CameraFrustumFarZInMeters.ToString());
                Console.WriteLine("");
                Console.WriteLine("Hmd Caps: " + hmd.HmdCaps.ToString());
                Console.WriteLine("Tracking Caps: " + hmd.TrackingCaps.ToString());
                Console.WriteLine("Distortion Caps: " + hmd.DistortionCaps.ToString());
                Console.WriteLine("");
                Console.WriteLine("Resolution: " + hmd.Resolution.w.ToString() + " * " + hmd.Resolution.h.ToString());
                Console.WriteLine("Windows Pos: " + hmd.WindowsPos.x.ToString() + ", " + hmd.WindowsPos.y.ToString());
                Console.WriteLine("");
                Console.WriteLine("Default Eye Fov: " + hmd.DefaultEyeFov[0].UpTan.ToString() + ", " + hmd.DefaultEyeFov[1].UpTan.ToString());
                Console.WriteLine("Max Eye Fov: " + hmd.MaxEyeFov[0].UpTan.ToString() + ", " + hmd.MaxEyeFov[1].UpTan.ToString());
                Console.WriteLine("");
                Console.WriteLine("Eye Render Order: " + hmd.EyeRenderOrder[0].ToString() + ", " + hmd.EyeRenderOrder[1].ToString());
                Console.WriteLine("");
                Console.WriteLine("Display Device Name: " + hmd.DisplayDeviceName);
                Console.WriteLine("Display ID: " + hmd.DisplayId.ToString());
            }

            OvrHmd.Destroy(hmd);
            OvrHmd.Shutdown();
        }
    }
}
