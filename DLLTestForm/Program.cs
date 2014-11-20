using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace DLLTestForm
{
    static class Program
    {
        /// <summary>
        /// アプリケーションのメイン エントリ ポイントです。
        /// </summary>
        [STAThread]
        static void Main()
        {
            //Application.EnableVisualStyles();
            //Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new Form1());

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            const double fps = 75.0;
            const double waitTime = 1000.0 / fps;

            long time1 = 0;
            long time2 = 1;
            float mesuredFps = 1000.0f / (time2 - time1);

            var mainWindow = new MainWindow();
            mainWindow.Show();

            System.Diagnostics.Stopwatch fpsController = new System.Diagnostics.Stopwatch();
            fpsController.Start();

            double targetTime;
            targetTime = (double)fpsController.ElapsedMilliseconds;
            targetTime += waitTime;
            while (mainWindow.Created)
            {

                time2 = time1;
                time1 = fpsController.ElapsedMilliseconds;
                Debug.WriteLine(1000.0f / (float)(time1 - time2));

                mainWindow.MainLoop();

                Application.DoEvents();

            }
        }
    }
}
