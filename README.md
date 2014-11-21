OculusRiftDK2.NET
=================
This repositry includes a C# wrapper and sample programs for Oculus SDK 0.4.x to use Oculus Rift DK2 from C# and OpenTK.

VS2013 solution
=================
This solution is inplemented by Visual Studio 2013. It consists of:

OculusDK2.NET
=================
This is wrapper of the CAPIs of Oculus. The wrapper is written by C++/CLI. The project generates "OculusDK2.NET.dll."

DLLMinimumTest
=================
This is a very simple C# console program showing how to use the wrapper of Oculus SDK.

DLLTestForm
=================
This is a sample program that displaying distorted stereo image on the Oculus DK2 from C#(Windows Form) and OpenTK. The program runs on "Extended Desktop Mode," and the stereo image is rendered by "Clienet Distortion Rendering Mode." 
