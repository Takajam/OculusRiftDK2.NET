// OculusDK2.NET.h
// Oculus SDK 0.4.3 CAPIÇÃÉâÉbÉpÅ[

#pragma once

//Oculus SDK 0.4.x
#define OVR_OS_WIN32
#define OVR_D3D_VERSION 11

#define OvrEyeCount 2

#include "OVR.h"
#include "LibOVR\Src\OVR_CAPI.h"
#include "LibOVR\Src\OVR_CAPI_GL.h"
#include "LibOVR\Src\OVR_CAPI_D3D.h"

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "shell32.lib")

#ifdef _DEBUG
#pragma comment(lib, "libovrd.lib")
#else
#pragma comment(lib, "libovr.lib")
#endif



using namespace System;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;


namespace OculusDK2NET {
	public ref class Vector2i
	{
	public:
		Vector2i()
		{
			ptr = new ovrVector2i;
		}

		Vector2i(int x, int y)
		{
			ptr = new ovrVector2i;
			ptr->x = x;
			ptr->y = y;
		}

		~Vector2i()
		{
			this->!Vector2i();
		}

		!Vector2i()
		{
			if (!undeletable) delete ptr;
		}
		
		property int x
		{
			int get(){ return ptr->x; }
			void set(int value) { ptr->x = value; }
		}

		property int y
		{
			int get(){ return ptr->y; }
			void set(int value) { ptr->y = value; }
		}

	internal:
		ovrVector2i* ptr;
		bool undeletable = false;

		Vector2i(ovrVector2i* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrVector2i;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}
		
		property ovrVector2i Native
		{
			ovrVector2i get() { return *ptr; }
		}
	};
	
	public ref class Sizei
	{
	public:
		Sizei()
		{
			ptr = new ovrSizei;
		}

		Sizei(int w, int h)
		{
			ptr = new ovrSizei;
			ptr->w = w; 
			ptr->h = h;			
		}

		~Sizei()
		{
			this->!Sizei();
		}

		!Sizei()
		{
			if (!undeletable) delete ptr;
		}

		property int w
		{
			int get() { return ptr->w; }
			void set(int value) { ptr->w = value; }
		}

		property int h
		{
			int get() { return ptr->h; }
			void set(int value) { ptr->h = value; }
		}

	internal:
		ovrSizei* ptr;
		bool undeletable = false;

		Sizei(ovrSizei* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrSizei;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrSizei Native
		{
			ovrSizei get() { return *ptr; }
		}
	};
	
	public ref class Recti
	{
	public:
		Recti()
		{
			ptr = new ovrRecti;
		}

		Recti(int x, int y, int w, int h)
		{
			ptr = new ovrRecti;
			ptr->Pos.x = x;
			ptr->Pos.y = y;
			ptr->Size.w = w; 
			ptr->Size.h = h;			
		}

		Recti(Vector2i^ pos, Sizei^ size)
		{
			ptr = new ovrRecti;
			ptr->Pos = pos->Native;
			ptr->Size = size->Native;
		}

		~Recti()
		{
			this->!Recti();
		}

		!Recti()
		{
			if (!undeletable) delete ptr;
		}

		property Vector2i^ Pos
		{
			Vector2i^ get() { return gcnew Vector2i(&(ptr->Pos), true); }
			void set(Vector2i^ value) { ptr->Pos = value->Native; }
		}

		property Sizei^ Size
		{
			Sizei^ get(){ return gcnew Sizei(&(ptr->Size), true); }
			void set(Sizei^ value) { ptr->Size = value->Native; }
		}

	internal:
		ovrRecti* ptr;
		bool undeletable = false;

		Recti(ovrRecti* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrRecti;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrRecti Native
		{
			ovrRecti get() { return *ptr; }
		}
	};
		
	public ref class Quatf
	{
	public:
		Quatf()
		{
			ptr = new ovrQuatf;
		}

		Quatf(float x, float y, float z, float w)
		{
			ptr = new ovrQuatf;
			ptr->x = x;
			ptr->y = y;
			ptr->z = z;
			ptr->w = w;
		}

		~Quatf()
		{
			this->!Quatf();
		}

		!Quatf()
		{
			if (!undeletable) delete ptr;
		}
		
		property float x
		{
			float get() { return ptr->x; }
			void set(float value) { ptr->x = value; }
		}

		property float y
		{
			float get() { return ptr->y; }
			void set(float value) { ptr->y = value; }
		}

		property float z
		{
			float get() { return ptr->z; }
			void set(float value) { ptr->z = value; }
		}

		property float w
		{
			float get() { return ptr->w; }
			void set(float value) { ptr->w = value; }
		}

		void Quatf::GetEulerAngles([Runtime::InteropServices::Out] float% yaw, [Runtime::InteropServices::Out] float% pitch, [Runtime::InteropServices::Out] float% roll)
		{
			float yawNative, pitchNative, rollNative;

			OVR::Quatf* q = new OVR::Quatf(ptr->x, ptr->y, ptr->z, ptr->w);
			q->GetEulerAngles <OVR::Axis::Axis_Y, OVR::Axis::Axis_X, OVR::Axis::Axis_Z>(&yawNative, &pitchNative, &rollNative);

			yaw = yawNative;
			pitch = pitchNative;
			roll = rollNative;

			delete q;
		}

		Quatf^ Quatf::Inverted()
		{
			OVR::Quatf* q = new OVR::Quatf(ptr->x, ptr->y, ptr->z, ptr->w);
			OVR::Quatf qi = q->Inverted();

			delete q;

			return gcnew Quatf(qi.x, qi.y, qi.z, qi.w);
		}

	internal:
		ovrQuatf* ptr;
		bool undeletable = false;

		Quatf(ovrQuatf* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrQuatf;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrQuatf Native
		{
			ovrQuatf get() { return *ptr; }
		}
	};

	public ref class Vector2f
	{
	public:
		Vector2f()
		{
			ptr = new ovrVector2f;
		}

		Vector2f(float x, float y)
		{
			ptr = new ovrVector2f;
			ptr->x = x;
			ptr->y = y;
		}
				
		property float x
		{
			float get() { return ptr->x; }
			void set(float value) { ptr->x = value; }
		}

		property float y
		{
			float get() { return ptr->y; }
			void set(float value) { ptr->y = value; }
		}

	internal:
		ovrVector2f* ptr;
		bool undeletable = false;

		Vector2f(ovrVector2f* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrVector2f;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrVector2f Native
		{
			ovrVector2f get() { return *ptr; }
		}
	};
		
	public ref class Vector3f
	{
	public:
		Vector3f()
		{
			ptr = new ovrVector3f;
		}

		Vector3f(float x, float y, float z)
		{
			ptr = new ovrVector3f;
			ptr->x = x;
			ptr->y = y;
			ptr->z = z;
		}

		~Vector3f()
		{
			this->!Vector3f();
		}

		!Vector3f()
		{
			if (!undeletable) delete ptr;
		}
		
		property float x
		{
			float get(){ return ptr->x; }
			void set(float value){ ptr->x = value; }
		}

		property float y
		{
			float get(){ return ptr->y; }
			void set(float value){ ptr->y = value; }
		}

		property float z
		{
			float get() { return ptr->z; }
			void set(float value) { ptr->z = value; }
		}

	internal:
		ovrVector3f* ptr;
		bool undeletable = false;
		
		Vector3f(ovrVector3f* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrVector3f;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrVector3f Native
		{
			ovrVector3f get() { return *ptr; }
		}
	};
		
	public ref class Matrix4f
	{
	public:
		Matrix4f()
		{
			ptr = new ovrMatrix4f;
		}

		Matrix4f(cli::array<cli::array<float>^>^ mat)
		{
			ptr = new ovrMatrix4f;
			for (int i = 0; i < mat->Length; i++)
			{
				for (int j = 0; j < mat[i]->Length; j++)
				{
					ptr->M[i][j] = mat[i][j];
				}
			}
		}

		Matrix4f(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			ptr = new ovrMatrix4f;
			ptr->M[0][0] = m00; ptr->M[0][1] = m01; ptr->M[0][2] = m02; ptr->M[0][3] = m03;
			ptr->M[1][0] = m10; ptr->M[1][1] = m11; ptr->M[1][2] = m12; ptr->M[1][3] = m13;
			ptr->M[2][0] = m20; ptr->M[2][1] = m21; ptr->M[2][2] = m22; ptr->M[2][3] = m23;
			ptr->M[3][0] = m30; ptr->M[3][1] = m31; ptr->M[3][2] = m32; ptr->M[3][3] = m33;
		}

		~Matrix4f()
		{
			this->!Matrix4f();
		}

		!Matrix4f()
		{
			if (!undeletable) delete ptr;
		}

		property cli::array<cli::array<float>^>^ M
		{
			cli::array<cli::array<float>^>^ get()
			{
				cli::array<cli::array<float>^>^ ret = gcnew cli::array<cli::array<float>^>(4);
				for (int i = 0; i < ret->Length; i++)
				{
					ret[i] = gcnew cli::array<float> (4);
					ret[i][0] = ptr->M[i][0];
					ret[i][1] = ptr->M[i][1];
					ret[i][2] = ptr->M[i][2];
					ret[i][3] = ptr->M[i][3];
				}

				return ret;
			}

			void set(cli::array<cli::array<float>^>^ value)
			{
				for (int i = 0; i < value->Length; i++)
				{					
						ptr->M[i][0] = value[i][0];
						ptr->M[i][1] = value[i][1];
						ptr->M[i][2] = value[i][2];
						ptr->M[i][3] = value[i][3];
				}
			}
		}

		property float M00
		{
			float get() { return ptr->M[0][0]; }
			void set(float value) { ptr->M[0][0] = value; }
		}

		property float M01
		{
			float get() { return ptr->M[0][1]; }
			void set(float value) { ptr->M[0][1] = value; }
		}

		property float M02
		{
			float get() { return ptr->M[0][2]; }
			void set(float value) { ptr->M[0][2] = value; }
		}

		property float M03
		{
			float get() { return ptr->M[0][3]; }
			void set(float value) { ptr->M[0][3] = value; }
		}

		property float M10
		{
			float get() { return ptr->M[1][0]; }
			void set(float value) { ptr->M[1][0] = value; }
		}

		property float M11
		{
			float get() { return ptr->M[1][1]; }
			void set(float value) { ptr->M[1][1] = value; }
		}

		property float M12
		{
			float get() { return ptr->M[1][2]; }
			void set(float value) { ptr->M[1][2] = value; }
		}

		property float M13
		{
			float get() { return ptr->M[1][3]; }
			void set(float value) { ptr->M[1][3] = value; }
		}

		property float M20
		{
			float get() { return ptr->M[2][0]; }
			void set(float value) { ptr->M[2][0] = value; }
		}

		property float M21
		{
			float get() { return ptr->M[2][1]; }
			void set(float value) { ptr->M[2][1] = value; }
		}

		property float M22
		{
			float get() { return ptr->M[2][2]; }
			void set(float value) { ptr->M[2][2] = value; }
		}

		property float M23
		{
			float get() { return ptr->M[2][3]; }
			void set(float value) { ptr->M[2][3] = value; }
		}

		property float M30
		{
			float get() { return ptr->M[3][0]; }
			void set(float value) { ptr->M[3][0] = value; }
		}

		property float M31
		{
			float get() { return ptr->M[3][1]; }
			void set(float value) { ptr->M[3][1] = value; }
		}

		property float M32
		{
			float get() { return ptr->M[3][2]; }
			void set(float value) { ptr->M[3][2] = value; }
		}

		property float M33
		{
			float get() { return ptr->M[3][3]; }
			void set(float value) { ptr->M[3][3] = value; }
		}

	internal:
		ovrMatrix4f* ptr;
		bool undeletable = false;

		Matrix4f(ovrMatrix4f* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrMatrix4f;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrMatrix4f Native
		{
			ovrMatrix4f get() { return *ptr; }
		}
	};
	
	public ref class Posef
	{
	public:
		Posef()
		{
			ptr = new ovrPosef;
		}

		Posef(float posx, float posy, float posz, float orientx, float orienty, float orientz, float orientw)
		{
			ptr = new ovrPosef;
			ptr->Position.x = posx;
			ptr->Position.y = posy;
			ptr->Position.z = posz;

			ptr->Orientation.x = orientx;
			ptr->Orientation.y = orienty;
			ptr->Orientation.z = orientz;
			ptr->Orientation.w = orientw;
		}

		Posef(Vector3f^ position, Quatf^ orientation)
		{
			ptr = new ovrPosef;
			ptr->Position = position->Native;
			ptr->Orientation = orientation->Native;
		}

		~Posef()
		{
			this->!Posef();
		}

		!Posef()
		{
			if (!undeletable) delete ptr;
		}

		property Quatf^ Orientation
		{
			Quatf^ get(){ return gcnew Quatf(&(ptr->Orientation), true); }
		}
		
		property Vector3f^ Position
		{
			Vector3f^ get() { return gcnew Vector3f(&(ptr->Position), true); }
		}

	internal:
		ovrPosef* ptr;
		bool undeletable = false;

		Posef(ovrPosef* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrPosef;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrPosef Native
		{
			ovrPosef get() { return *ptr; }
		}
	};

	public ref class PoseStatef
	{
	public:
		PoseStatef()
		{
			ptr = new ovrPoseStatef;
		}

		~PoseStatef()
		{
			this->!PoseStatef();
		}

		!PoseStatef()
		{
			if (!undeletable) delete ptr;
		}

		property Posef^ ThePose
		{
			Posef^ get() { return gcnew Posef(&(ptr->ThePose), true); }
		}

		property Vector3f^ AngularVelocity
		{
			Vector3f^ get() { return gcnew Vector3f(&(ptr->AngularVelocity), true); }
		}

		property Vector3f^ LinearVelocity
		{
			Vector3f^ get(){ return gcnew Vector3f(&(ptr->LinearVelocity), true); }
		}

		property Vector3f^ AngularAcceleration
		{
			Vector3f^ get() { return gcnew Vector3f(&(ptr->AngularAcceleration), true); }
		}

		property Vector3f^ LinearAcceleration
		{
			Vector3f^ get() { return gcnew Vector3f(&(ptr->LinearAcceleration), true); }
		}

		property double TimeInSeconds
		{
			double get() { return ptr->TimeInSeconds; }
		} 

	internal:
		ovrPoseStatef* ptr;
		bool undeletable = false;

		PoseStatef(ovrPoseStatef* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrPoseStatef;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrPoseStatef Native
		{
			ovrPoseStatef get() { return *ptr; }
		}
	};
		
	public ref class FovPort
	{
	public:
		FovPort()
		{
			ptr = new ovrFovPort;
		}

		FovPort(float upTan, float downTan, float leftTan, float rightTan)
		{
			ptr = new ovrFovPort;
			ptr->UpTan = upTan;
			ptr->DownTan = downTan;
			ptr->LeftTan = leftTan;
			ptr->RightTan = rightTan;
		}

		~FovPort()
		{
			this->!FovPort();
		}

		!FovPort()
		{
			if (!undeletable) delete ptr;
		}

		property float UpTan
		{
			float get() { return ptr->UpTan; }
			void set(float value) { ptr->UpTan = value; }
		}
		
		property float DownTan
		{
			float get() { return ptr->DownTan; }
			void set(float value) { ptr->DownTan = value; }
		}

		property float LeftTan
		{
			float get() { return ptr->LeftTan; }
			void set(float value) { ptr->LeftTan = value; }
		}

		property float RightTan
		{
			float get() { return ptr->RightTan; }
			void set(float value) { ptr->RightTan = value; }
		}

	internal:
		ovrFovPort* ptr;
		bool undeletable = false;

		FovPort(ovrFovPort* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrFovPort;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrFovPort Native
		{
			ovrFovPort get() { return *ptr; }
		}
	};

	public enum class HmdType : unsigned int
	{
		None = 0,
		DK1 = 3,
		DKHD = 4,
		DK2 = 6,
		Other
	};

	public enum class HmdCaps : unsigned int
	{
		Present = 0x0001,
		Available = 0x0002,
		Captured = 0x0004,

		ExtendDesktop = 0x0008,

		NoMirrorToWindow = 0x2000,
		DisplayOff = 0x0040,

		LowPersistence = 0x0080,
		DynamicPrediction = 0x0200,
		NoVSync = 0x1000,

		WritableMask = 0x33F0,
		ServiceMask = 0x23F0
	};

	public enum class TrackingCaps : unsigned int
	{
		Orientation = 0x0010,
		MagYawCorrection = 0x0020,
		Position = 0x0040,
		Idle = 0x0100
	};

	public enum class DistortionCaps : unsigned int
	{
		Chromatic = 0x01,
		TimeWarp = 0x02,
		Vignette = 0x08,
		NoRestore = 0x10,
		FlipInput = 0x20,
		SRGB = 0x40,
		Overdrive = 0x80,
		
		ProfileNoTimewarpSpinWaits = 0x10000
	};

	public enum class EyeType : unsigned int
	{
		Left = 0,
		Right = 1,
		Count = 2
	};
		
	public ref class HmdDesc
	{
	public:
		HmdDesc()
		{
			ptr = new ovrHmdDesc;
		}

		~HmdDesc()
		{
			this->!HmdDesc();
		}

		!HmdDesc()
		{
			if (!undeletable) delete ptr;
		}

		property IntPtr Handle
		{
			IntPtr get() { return (IntPtr)ptr->Handle; }
		}

		property HmdType Type
		{
			HmdType get() { return (HmdType)ptr->Type; }
		}

		property String^ ProductName
		{
			String^ get() { return gcnew String(ptr->ProductName); }
		}

		property String^ Manufacturer
		{
			String^ get() { return gcnew String(ptr->Manufacturer); }
		}

		property short VendorId
		{
			short get() { return ptr->VendorId; }
		}

		property short ProductId
		{
			short get() { return ptr->ProductId; }
		}

		property String^ SerialNumber
		{
			String^ get() { return gcnew String(ptr->SerialNumber); }
		}

		property short FirmwareMajor
		{
			short get() { return ptr->FirmwareMajor; }
		}

		property short FirmwareMinor
		{
			short get() { return ptr->FirmwareMinor; }
		}

		property float CameraFrustumHFovInRadians
		{
			float get() { return ptr->CameraFrustumHFovInRadians; }
		}

		property float CameraFrustumVFovInRadians
		{
			float get() { return ptr->CameraFrustumVFovInRadians; }
		}

		property float CameraFrustumNearZInMeters
		{
			float get() { return ptr->CameraFrustumHFovInRadians; }
		}

		property float CameraFrustumFarZInMeters
		{
			float get() { return ptr->CameraFrustumNearZInMeters; }
		}

		property HmdCaps HmdCaps
		{
			OculusDK2NET::HmdCaps get(){ return (OculusDK2NET::HmdCaps)ptr->HmdCaps; }
		}

		property TrackingCaps TrackingCaps
		{
			OculusDK2NET::TrackingCaps get(){ return (OculusDK2NET::TrackingCaps)ptr->TrackingCaps; }
		}

		property DistortionCaps DistortionCaps
		{
			OculusDK2NET::DistortionCaps get(){ return (OculusDK2NET::DistortionCaps)ptr->DistortionCaps; }
		}

		property array<FovPort^>^ DefaultEyeFov
		{
			array<FovPort^>^ get()
			{ 
				array<FovPort^>^ ret = gcnew array<FovPort^>(2);
				
				ret[0] = gcnew FovPort(&(ptr->DefaultEyeFov[0]), false);
				ret[1] = gcnew FovPort(&(ptr->DefaultEyeFov[1]), false);

				return ret;
			}
		}

		property array<FovPort^>^ MaxEyeFov
		{
			array<FovPort^>^ get()
			{
				array<FovPort^>^ ret = gcnew array<FovPort^>(2);

				ret[0] = gcnew FovPort(&(ptr->MaxEyeFov[0]), false);
				ret[1] = gcnew FovPort(&(ptr->MaxEyeFov[1]), false);

				return ret;
			}
		}

		property System::Collections::Generic::List<EyeType>^ EyeRenderOrder
		{
			System::Collections::Generic::List<EyeType>^ get()
			{
				System::Collections::Generic::List<EyeType>^ ret = gcnew System::Collections::Generic::List<EyeType>(2);

				ret->Add((EyeType)ptr->EyeRenderOrder[0]);
				ret->Add((EyeType)ptr->EyeRenderOrder[1]);

				return ret;
			}
		}

		property Sizei^ Resolution
		{
			Sizei^ get() { return gcnew Sizei(&(ptr->Resolution), false); }
		}

		property Vector2i^ WindowsPos
		{
			Vector2i^ get() { return gcnew Vector2i(&(ptr->WindowsPos), false); }
		}

		property String^ DisplayDeviceName
		{
			String^ get() { return gcnew String(ptr->DisplayDeviceName); }
		}

		property int DisplayId
		{
			int get() { return ptr->DisplayId; }
		}

	internal:
		ovrHmdDesc* ptr;
		bool undeletable = false;

		HmdDesc(ovrHmdDesc* vi)
		{
			undeletable = true;
			ptr = vi;
		}

		HmdDesc(ovrHmd vi)
		{
			undeletable = true;
			ptr = (ovrHmdDesc*)vi;
		}

		property ovrHmd Native
		{
			ovrHmd get() { return ptr; }
		}
	};

	public enum class StatusBits : unsigned int
	{
		OrientationTracked = 0x0001,
		PositionTracked = 0x0002,
		CameraPoseTracked = 0x0004,
		PositionConnected = 0x0020,
		HmdConnected = 0x0080
	};
		
	public ref class SensorData
	{
	public:
		SensorData()
		{
			ptr = new ovrSensorData;
		}

		~SensorData()
		{
			this->!SensorData();
		}

		!SensorData()
		{
			if (!undeletable) delete ptr;
		}

		property Vector3f^ Accelerometer
		{
			Vector3f^ get() { return gcnew Vector3f(&(ptr->Accelerometer), false); }
		}

		property Vector3f^ Gyro
		{
			Vector3f^ get() { return gcnew Vector3f(&(ptr->Gyro), false); }
		}

		property Vector3f^ Magnetometer
		{
			Vector3f^ get() { return gcnew Vector3f(&(ptr->Magnetometer), false); }
		}

		property float Temperature
		{
			float get() { return ptr->Temperature; }
		}

		property float TimeInSeconds
		{
			float get() { return ptr->TimeInSeconds; }
		}

	internal:
		ovrSensorData* ptr;
		bool undeletable = false;

		SensorData(ovrSensorData* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrSensorData;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrSensorData Native
		{
			ovrSensorData get() { return *ptr; }
		}
	};
		
	public ref class TrackingState
	{
	public:
		TrackingState()
		{
			ptr = new ovrTrackingState;
		}

		~TrackingState()
		{
			this->!TrackingState();
		}

		!TrackingState()
		{
			if (!undeletable) delete ptr;
		}

		property PoseStatef^ HeadPose
		{
			PoseStatef^ get() { return gcnew PoseStatef(&(ptr->HeadPose), false); }
		}

		property Posef^ CameraPose
		{
			Posef^ get() { return gcnew Posef(&(ptr->CameraPose), false); }
		}

		property Posef^ LeveledCameraPose
		{
			Posef^ get() { return gcnew Posef(&(ptr->LeveledCameraPose), false); }
		}

		property SensorData^ RawSensorData
		{
			SensorData^ get() { return gcnew SensorData(&(ptr->RawSensorData), false); }
		}

		property StatusBits StatusFlags
		{
			StatusBits get() { return (StatusBits)ptr->StatusFlags; }
		}

	internal:
		ovrTrackingState* ptr;
		bool undeletable = false;

		TrackingState(ovrTrackingState* vi, bool undeletableFlag)
		{
			undeletableFlag = undeletable;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrTrackingState;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrTrackingState Native
		{
			ovrTrackingState get() { return *ptr; }
		}
	};
		
	public ref class FrameTiming
	{
	public:
		FrameTiming()
		{
			ptr = new ovrFrameTiming;
		}

		~FrameTiming()
		{
			this->!FrameTiming();
		}

		!FrameTiming()
		{
			if (!undeletable) delete ptr;
		}

		property float DeltaSeconds
		{
			float get() { return ptr->DeltaSeconds; }
		}

		property double ThisFrameSeconds
		{
			double get() { return ptr->ThisFrameSeconds; }
		}

		property double TimewarpPointSeconds
		{
			double get() { return ptr->TimewarpPointSeconds; }
		}

		property double NextFrameSeconds
		{
			double get() { return ptr->NextFrameSeconds; }
		}

		property double ScanoutMidpointSeconds
		{
			double get() { return ptr->ScanoutMidpointSeconds; }
		}

		property cli::array<double>^ EyeScanoutSeconds
		{
			cli::array<double>^ get()
			{
				cli::array<double>^ ret = gcnew cli::array<double> (2);

				ret[0] = ptr->EyeScanoutSeconds[0];
				ret[1] = ptr->EyeScanoutSeconds[1];

				return ret;
			}
		}

	internal:
		ovrFrameTiming* ptr;
		bool undeletable = false;

		FrameTiming(ovrFrameTiming* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrFrameTiming;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrFrameTiming Native
		{
			ovrFrameTiming get(){ return *ptr; }
		}
	};
		
	public ref class EyeRenderDesc
	{
	public:
		EyeRenderDesc()
		{
			ptr = new ovrEyeRenderDesc;
		}

		~EyeRenderDesc()
		{
			this->!EyeRenderDesc();
		}

		!EyeRenderDesc()
		{
			if (!undeletable) delete ptr;
		}

		property EyeType Eye
		{
			EyeType get() { return (EyeType)ptr->Eye; }
		}

		property FovPort^ Fov
		{
			FovPort^ get() { return gcnew FovPort(&(ptr->Fov), false); }
		}

		property Recti^ DistortedViewport
		{
			Recti^ get() { return gcnew Recti(&(ptr->DistortedViewport), false); }
		}

		property Vector2f^ PixelsPerTanAngleAtCenter
		{
			Vector2f^ get() { return gcnew Vector2f(&(ptr->PixelsPerTanAngleAtCenter), false); }
		}

		property Vector3f^ HmdToEyeViewOffset
		{
			Vector3f^ get() { return gcnew Vector3f(&(ptr->HmdToEyeViewOffset), false); }
		}

	internal:
		ovrEyeRenderDesc* ptr;
		bool undeletable = false;

		EyeRenderDesc(ovrEyeRenderDesc* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrEyeRenderDesc;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrEyeRenderDesc Native
		{
			ovrEyeRenderDesc get(){ return *ptr; }
		}
	};

	public enum class RenderApiType
	{
		None,
		OpenGL,
		Android_GLES,
		D3D9,
		D3D10,
		D3D11,
		Count
	};
	
	public ref class RenderApiConfigHeader
	{
	public:
		RenderApiConfigHeader()
		{
			ptr = new ovrRenderAPIConfigHeader;
		}

		RenderApiConfigHeader(RenderApiType api, Sizei^ rtSize, int multisample)
		{
			ptr = new ovrRenderAPIConfigHeader;
			ptr->API = (ovrRenderAPIType)api;
			ptr->RTSize = rtSize->Native;
			ptr->Multisample = multisample;
		}

		~RenderApiConfigHeader()
		{
			this->!RenderApiConfigHeader();
		}

		!RenderApiConfigHeader()
		{
			if (!undeletable) delete ptr;
		}

		property RenderApiType Api
		{
			RenderApiType get(){ return (RenderApiType)ptr->API; }
			void set(RenderApiType value) { ptr->API = (ovrRenderAPIType)value; }
		}

		property Sizei^ RtSize
		{
			Sizei^ get() { return gcnew Sizei(&(ptr->RTSize), true); }
			void set(Sizei^ value){ ptr->RTSize = value->Native; }
		}

		property int Multisample
		{
			int get() { return ptr->Multisample; }
			void set(int value) { ptr->Multisample = value; }
		}

	internal:
		ovrRenderAPIConfigHeader* ptr;
		bool undeletable = false;

		RenderApiConfigHeader(ovrRenderAPIConfigHeader* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrRenderAPIConfigHeader;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrRenderAPIConfigHeader Native
		{
			ovrRenderAPIConfigHeader get() { return *ptr; }
		}

	};
		
	public ref class RenderApiConfig
	{
	public:
		RenderApiConfig()
		{
			ptr = new ovrRenderAPIConfig;
		}

		RenderApiConfig(RenderApiConfigHeader^ header, cli::array<UIntPtr>^ platformData)
		{
			ptr = new ovrRenderAPIConfig;
			ptr->Header = header->Native;
			for (int i = 0; i < platformData->Length; i++)
			{
				ptr->PlatformData[i] = (uintptr_t)platformData[i];
			}
		}

		~RenderApiConfig()
		{
			this->!RenderApiConfig();
		}

		!RenderApiConfig()
		{
			if (!undeletable) delete ptr;
		}

		property RenderApiConfigHeader^ Header
		{
			RenderApiConfigHeader^ get() { return gcnew RenderApiConfigHeader(&(ptr->Header), true); }
			void set(RenderApiConfigHeader^ value) { ptr->Header = value->Native; }
		}

		property cli::array<UIntPtr>^ PlatformData
		{
			cli::array<UIntPtr>^ get() 
			{
				cli::array<UIntPtr>^ ret = gcnew cli::array<UIntPtr>(8);

				ret[0] = (UIntPtr)ptr->PlatformData[0];
				ret[1] = (UIntPtr)ptr->PlatformData[1];
				ret[2] = (UIntPtr)ptr->PlatformData[2];
				ret[3] = (UIntPtr)ptr->PlatformData[3];
				ret[4] = (UIntPtr)ptr->PlatformData[4];
				ret[5] = (UIntPtr)ptr->PlatformData[5];
				ret[6] = (UIntPtr)ptr->PlatformData[6];
				ret[7] = (UIntPtr)ptr->PlatformData[7];

				return ret;
			}

			void set(cli::array<UIntPtr>^ value)
			{
				ptr->PlatformData[0] = (uintptr_t)value[0];
				ptr->PlatformData[1] = (uintptr_t)value[1];
				ptr->PlatformData[2] = (uintptr_t)value[2];
				ptr->PlatformData[3] = (uintptr_t)value[3];
				ptr->PlatformData[4] = (uintptr_t)value[4];
				ptr->PlatformData[5] = (uintptr_t)value[5];
				ptr->PlatformData[6] = (uintptr_t)value[6];
				ptr->PlatformData[7] = (uintptr_t)value[7];
			}
		}

	internal:
		ovrRenderAPIConfig* ptr;
		bool undeletable = false;

		RenderApiConfig(ovrRenderAPIConfig* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrRenderAPIConfig;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrRenderAPIConfig Native
		{
			ovrRenderAPIConfig get() { return *ptr; }
		}

	};
		
	public ref class TextureHeader
	{
	public:
		TextureHeader()
		{
			ptr = new ovrTextureHeader;
		}

		TextureHeader(RenderApiType api, Sizei^ textureSize, Recti^ renderViewport)
		{
			ptr = new ovrTextureHeader;
			ptr->API = (ovrRenderAPIType)api;
			ptr->TextureSize = textureSize->Native;
			ptr->RenderViewport = renderViewport->Native;
		}

		~TextureHeader()
		{
			this->!TextureHeader();
		}

		!TextureHeader()
		{
			if (!undeletable) delete ptr;
		}

		property RenderApiType Api
		{
			RenderApiType get() { return (RenderApiType)ptr->API; }
			void set(RenderApiType value) { ptr->API = (ovrRenderAPIType)value; }
		}

		property Sizei^ TextureSize
		{
			Sizei^ get() { return gcnew Sizei(&(ptr->TextureSize), true); }
			void set(Sizei^ value) { ptr->TextureSize = value->Native; }
		}

		property Recti^ RenderViewport
		{
			Recti^ get() { return gcnew Recti(&(ptr->RenderViewport), true); }
			void set(Recti^ value) { ptr->RenderViewport = value->Native; }
		}

	internal:
		ovrTextureHeader* ptr;
		bool undeletable = false;

		TextureHeader(ovrTextureHeader* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrTextureHeader;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrTextureHeader Native
		{
			ovrTextureHeader get() { return *ptr; }
		}
	};

	
	public ref class Texture
	{
	public:
		Texture()
		{
			ptr = new ovrTexture;
		}

		Texture(TextureHeader^ header, cli::array<UIntPtr>^ platformData)
		{
			ptr = new ovrTexture;
			ptr->Header = header->Native;
			for (int i = 0; i < platformData->Length; i++)
			{
				ptr->PlatformData[i] = (uintptr_t)platformData[i];
			}
		}

		~Texture()
		{
			this->!Texture();
		}

		!Texture()
		{
			if (!undeletable) delete ptr;
		}

		property TextureHeader^ Header
		{
			TextureHeader^ get() { return gcnew TextureHeader(&(ptr->Header), true); }
			void set(TextureHeader^ value) { ptr->Header = value->Native; }
		}

		property cli::array<UIntPtr>^ PlatformData
		{
			cli::array<UIntPtr>^ get()
			{
				cli::array<UIntPtr>^ ret = gcnew cli::array<UIntPtr>(8);

				ret[0] = (UIntPtr)ptr->PlatformData[0];
				ret[1] = (UIntPtr)ptr->PlatformData[1];
				ret[2] = (UIntPtr)ptr->PlatformData[2];
				ret[3] = (UIntPtr)ptr->PlatformData[3];
				ret[4] = (UIntPtr)ptr->PlatformData[4];
				ret[5] = (UIntPtr)ptr->PlatformData[5];
				ret[6] = (UIntPtr)ptr->PlatformData[6];
				ret[7] = (UIntPtr)ptr->PlatformData[7];

				return ret;
			}

			void set(cli::array<UIntPtr>^ value)
			{
				ptr->PlatformData[0] = (uintptr_t)value[0];
				ptr->PlatformData[1] = (uintptr_t)value[1];
				ptr->PlatformData[2] = (uintptr_t)value[2];
				ptr->PlatformData[3] = (uintptr_t)value[3];
				ptr->PlatformData[4] = (uintptr_t)value[4];
				ptr->PlatformData[5] = (uintptr_t)value[5];
				ptr->PlatformData[6] = (uintptr_t)value[6];
				ptr->PlatformData[7] = (uintptr_t)value[7];
			}
		}

	internal:
		ovrTexture* ptr;
		bool undeletable = false;

		Texture(ovrTexture* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrTexture;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrTexture Native
		{
			ovrTexture get() { return *ptr; }
		}
	};
	
	
	public ref class DistortionVertex
	{
	public:
		DistortionVertex()
		{
			ptr = new ovrDistortionVertex;
		}

		~DistortionVertex()
		{
			this->!DistortionVertex();
		}

		!DistortionVertex()
		{
			if (!undeletable) delete ptr;
		}

		property Vector2f^ ScreenPosNDC
		{
			Vector2f^ get() { return gcnew Vector2f(&(ptr->ScreenPosNDC), true); }
		}

		property float TimeWarpFactor
		{
			float get() { return ptr->TimeWarpFactor; }
		}

		property float VignetteFactor
		{
			float get() { return ptr->VignetteFactor; }
		}

		property Vector2f^ TanEyeAnglesR
		{
			Vector2f^ get(){ return gcnew Vector2f(&(ptr->TanEyeAnglesR), true); }
		}
		
		property Vector2f^ TanEyeAnglesG
		{
			Vector2f^ get(){ return gcnew Vector2f(&(ptr->TanEyeAnglesG), true); }
		}
		property Vector2f^ TanEyeAnglesB
		{
			Vector2f^ get(){ return gcnew Vector2f(&(ptr->TanEyeAnglesB), true); }
		}

	internal:
		ovrDistortionVertex* ptr;
		bool undeletable = false;

		DistortionVertex(ovrDistortionVertex* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrDistortionVertex;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrDistortionVertex Native
		{
			ovrDistortionVertex get() { return *ptr; }
		}
	};

	
	public ref class DistortionMesh
	{
	public:
		DistortionMesh()
		{
			ptr = new ovrDistortionMesh;
		}

		DistortionMesh(System::Collections::Generic::List<DistortionVertex^>^ vertexData, System::Collections::Generic::List<unsigned short>^ indexData, unsigned int vertexCount, unsigned int indexCount)
		{
			ptr = new ovrDistortionMesh;
			ptr->VertexCount = vertexCount;
			this->VertexData = vertexData;
			ptr->IndexCount = indexCount;
			this->IndexData = indexData;
		}

		~DistortionMesh()
		{
			this->!DistortionMesh();
		}

		!DistortionMesh()
		{
			if (!undeletable) delete ptr;
		}
		
		property System::Collections::Generic::List<DistortionVertex^>^ VertexData
		{
			System::Collections::Generic::List<DistortionVertex^>^ get()
			{
				System::Collections::Generic::List<DistortionVertex^>^ ret = gcnew System::Collections::Generic::List<DistortionVertex^>(ptr->VertexCount);
				for (unsigned int i = 0; i < ptr->VertexCount; i++)
				{
					ret->Add(gcnew DistortionVertex(&(ptr->pVertexData[i]), false));
				}

				return ret;
			}

			void set(System::Collections::Generic::List<DistortionVertex^>^ value)
			{
				ptr->VertexCount = value->Count;

				ptr->pVertexData = new ovrDistortionVertex[ptr->VertexCount];
				for (unsigned int i = 0; i < ptr->VertexCount; i++)
				{
					ptr->pVertexData[i] = value[i]->Native;
				}
			}
		}
		
		property System::Collections::Generic::List<unsigned short>^ IndexData
		{
			System::Collections::Generic::List<unsigned short>^ get()
			{
				System::Collections::Generic::List<unsigned short>^ ret = gcnew System::Collections::Generic::List<unsigned short>(ptr->IndexCount);
				for (unsigned int i = 0; i < ptr->IndexCount; i++)
				{
					ret->Add(ptr->pIndexData[i]);
				}

				return ret;
			}

			void set(System::Collections::Generic::List<unsigned short>^ value)
			{
				ptr->IndexCount = value->Count;

				ptr->pIndexData = new unsigned short[ptr->IndexCount];
				for (unsigned int i = 0; i < ptr->IndexCount; i++)
				{
					ptr->pIndexData[i] = value[i];
				}
			}
		}
		
		property unsigned int VertexCount
		{
			unsigned int get() { return ptr->VertexCount; }
			void set(unsigned int value) { ptr->VertexCount = value; }
		}

		property unsigned int IndexCount
		{
			unsigned int get() { return ptr->IndexCount; }
			void set(unsigned int value) { ptr->IndexCount = value; }
		}
	
	internal:
		ovrDistortionMesh* ptr;
		bool undeletable = false;

		DistortionMesh(ovrDistortionMesh* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrDistortionMesh;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrDistortionMesh Native
		{
			ovrDistortionMesh get(){ return *ptr; }
		}
	};

	
	public ref class HswDisplayState
	{
	public:
		HswDisplayState()
		{
			ptr = new ovrHSWDisplayState;
		}

		HswDisplayState(bool displayed, double startTime, double dismissibleTime)
		{
			ptr = new ovrHSWDisplayState;
			ptr->Displayed = (ovrBool)displayed;
			ptr->StartTime = startTime;
			ptr->DismissibleTime = dismissibleTime;
		}

		~HswDisplayState()
		{
			this->!HswDisplayState();
		}

		!HswDisplayState()
		{
			if (!undeletable) delete ptr;
		}

		property bool Displayed
		{
			bool get() { return ptr->Displayed != 0 ? true : false; }
		}

		property double StartTime
		{
			double get() { return ptr->StartTime; }
		}

		property double DismissibleTime
		{
			double get(){ return ptr->DismissibleTime; }
		}

	internal:
		ovrHSWDisplayState* ptr;
		bool undeletable = false;

		HswDisplayState(ovrHSWDisplayState* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrHSWDisplayState;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrHSWDisplayState Native
		{
			ovrHSWDisplayState get() { return *ptr; }
		}
	};
		
	public ref class GLConfigData
	{
	public:
		GLConfigData()
		{
			ptr = new ovrGLConfigData;
		}

		GLConfigData(RenderApiConfigHeader^ header, IntPtr window, IntPtr dc)
		{
			ptr = new ovrGLConfigData;
			ptr->Header = header->Native;
			ptr->Window = reinterpret_cast<HWND>(window.ToPointer());
			ptr->DC = reinterpret_cast<HDC>(dc.ToPointer());
		}

		~GLConfigData()
		{
			this->!GLConfigData();
		}

		!GLConfigData()
		{
			if (!undeletable) delete ptr;
		}

		property RenderApiConfigHeader^ Header
		{
			RenderApiConfigHeader^ get() { return gcnew RenderApiConfigHeader(&(ptr->Header), true); }
			void set(RenderApiConfigHeader^ value) { ptr->Header = value->Native; }
		}

		property IntPtr Window
		{
			IntPtr get() { return (IntPtr)ptr->Window; }
			void set(IntPtr value) { ptr->Window = reinterpret_cast<HWND>(value.ToPointer()); }
		}

		property IntPtr DC
		{
			IntPtr get(){ return (IntPtr)ptr->DC; }
			void set(IntPtr value){ ptr->DC = reinterpret_cast<HDC>(value.ToPointer()); }
		}

	internal:
		ovrGLConfigData* ptr;
		bool undeletable = false;

		GLConfigData(ovrGLConfigData* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrGLConfigData;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrGLConfigData Native
		{
			ovrGLConfigData get() { return *ptr; }
		}
	};

	
	public ref class GLConfig
	{
	public:
		GLConfig()
		{
			ptr = new ovrGLConfig;
		}			

		GLConfig(RenderApiConfig^ config, GLConfigData^ ogl)
		{
			ptr = new ovrGLConfig;
			ptr->Config = config->Native;
			ptr->OGL = ogl->Native;
		}

		~GLConfig()
		{
			this->!GLConfig();
		}

		!GLConfig()
		{
			if (!undeletable) delete ptr;
		}

		property RenderApiConfig^ Config
		{
			RenderApiConfig^ get() { return gcnew RenderApiConfig(&(ptr->Config), true); }
			void set(RenderApiConfig^ value) { ptr->Config = value->Native; }
		}

		property GLConfigData^ OGL
		{
			GLConfigData^ get() { return gcnew GLConfigData(&(ptr->OGL), true); }
			void set(GLConfigData^ value) { ptr->OGL = value->Native; }
		}

	internal:
		ovrGLConfig* ptr;
		bool undeletable = false;

		GLConfig(ovrGLConfig* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrGLConfig;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrGLConfig Native
		{
			ovrGLConfig get(){ return *ptr; }
		}
	};

	
	public ref class GLTextureData
	{
	public:
		GLTextureData()
		{
			ptr = new ovrGLTextureData;
		}

		GLTextureData(TextureHeader^ header, unsigned int texId)
		{
			ptr = new ovrGLTextureData;
			ptr->Header = header->Native;
			ptr->TexId = texId;
		}

		~GLTextureData()
		{
			this->!GLTextureData();
		}

		!GLTextureData()
		{
			if (!undeletable) delete ptr;
		}

		property TextureHeader^ Header
		{
			TextureHeader^ get() { return gcnew TextureHeader(&(ptr->Header), true); }
			void set(TextureHeader^ value) { ptr->Header = value->Native; }
		}

		property unsigned int TexId
		{
			unsigned int get() { return ptr->TexId; }
			void set(unsigned int value) { ptr->TexId = value; }
		}

	internal:
		ovrGLTextureData* ptr;
		bool undeletable = false;

		GLTextureData(ovrGLTextureData* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrGLTextureData;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrGLTextureData Native
		{
			ovrGLTextureData get() { return *ptr; }
		}
	};

	
	public ref class GLTexture
	{	
	public:
		GLTexture()
		{
			ptr = new ovrGLTexture;
		}

		GLTexture(Texture^ texture, GLTextureData^ ogl)
		{
			ptr = new ovrGLTexture;
			ptr->Texture = texture->Native;
			ptr->OGL = ogl->Native;
		}

		~GLTexture()
		{
			this->!GLTexture();
		}

		!GLTexture()
		{
			if (!undeletable) delete ptr;
		}

		property Texture^ Texture
		{
			OculusDK2NET::Texture^ get() { return gcnew OculusDK2NET::Texture(&(ptr->Texture), true); }
			void set(OculusDK2NET::Texture^ value) { ptr->Texture = value->Native; }
		}

		property GLTextureData^ OGL
		{
			GLTextureData^ get() { return gcnew GLTextureData(&(ptr->OGL), true); }
			void set(GLTextureData^ value){ ptr->OGL = value->Native; }
		}

	internal:
		ovrGLTexture* ptr;
		bool undeletable = false;

		GLTexture(ovrGLTexture* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrGLTexture;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrGLTexture Native
		{
			ovrGLTexture get() { return *ptr; }
		}
	};

	
	public ref class D3D11ConfigData
	{
	public:
		D3D11ConfigData()
		{
			ptr = new ovrD3D11ConfigData;
		}

		D3D11ConfigData(RenderApiConfigHeader^ header, IntPtr device, IntPtr deviceContext, IntPtr backBafferRT, IntPtr swapChain)
		{
			ptr = new ovrD3D11ConfigData;
			ptr->Header = header->Native;
			ptr->pDevice = reinterpret_cast<ID3D11Device*>(device.ToPointer());
			ptr->pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(deviceContext.ToPointer());
			ptr->pBackBufferRT = reinterpret_cast<ID3D11RenderTargetView*>(BackBafferRT.ToPointer());
			ptr->pSwapChain = reinterpret_cast<IDXGISwapChain*>(swapChain.ToPointer());
		}

		~D3D11ConfigData()
		{
			this->!D3D11ConfigData();
		}

		!D3D11ConfigData()
		{
			if (!undeletable) delete ptr;
		}

		property RenderApiConfigHeader^ Header
		{
			RenderApiConfigHeader^ get() { return gcnew RenderApiConfigHeader(&(ptr->Header), true); }
			void set(RenderApiConfigHeader^ value){ ptr->Header = value->Native; }
		}

		property IntPtr Device
		{
			IntPtr get() { return (IntPtr)ptr->pDevice; }
			void set(IntPtr value) { ptr->pDevice = reinterpret_cast<ID3D11Device*>(value.ToPointer()); }
		}

		property IntPtr DeviceContext
		{
			IntPtr get() { return (IntPtr)ptr->pDeviceContext; }
			void set(IntPtr value){ ptr->pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(value.ToPointer()); }
		}

		property IntPtr BackBafferRT
		{
			IntPtr get() { return (IntPtr)ptr->pBackBufferRT; }
			void set(IntPtr value){ ptr->pBackBufferRT = reinterpret_cast<ID3D11RenderTargetView*>(value.ToPointer()); }
		}

		property IntPtr SwapChain
		{
			IntPtr get() { return (IntPtr)ptr->pSwapChain; }
			void set(IntPtr value){ ptr->pSwapChain = reinterpret_cast <IDXGISwapChain*>(value.ToPointer()); }
		}

	internal:
		ovrD3D11ConfigData* ptr;
		bool undeletable = false;

		D3D11ConfigData(ovrD3D11ConfigData* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrD3D11ConfigData;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrD3D11ConfigData Native
		{
			ovrD3D11ConfigData get() { return *ptr; }
		}
	};

	
	public ref class D3D11Config
	{
	public:
		D3D11Config()
		{
			ptr = new ovrD3D11Config;
		}

		D3D11Config(RenderApiConfig^ config, D3D11ConfigData^ d3d11)
		{
			ptr = new ovrD3D11Config;
			ptr->Config = config->Native;
			ptr->D3D11 = d3d11->Native;
		}

		~D3D11Config()
		{
			this->!D3D11Config();
		}

		!D3D11Config()
		{
			if (!undeletable) delete ptr;
		}

		property RenderApiConfig^ Config
		{
			RenderApiConfig^ get() { return gcnew RenderApiConfig(&(ptr->Config), true); }
			void set(RenderApiConfig^ value) { ptr->Config = value->Native; }
		}

		property D3D11ConfigData^ D3D11
		{
			D3D11ConfigData^ get() { return gcnew D3D11ConfigData(&(ptr->D3D11), true); }
			void set(D3D11ConfigData^ value) { ptr->D3D11 = value->Native; }
		}

	internal:
		ovrD3D11Config* ptr;
		bool undeletable = false;

		D3D11Config(ovrD3D11Config* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrD3D11Config;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrD3D11Config Native
		{
			ovrD3D11Config get() { return *ptr; }
		}
	};

	
	public ref class D3D11TextureData
	{
	public:
		D3D11TextureData()
		{
			ptr = new ovrD3D11TextureData;
		}

		D3D11TextureData(TextureHeader^ header, IntPtr texture, IntPtr srView)
		{
			ptr = new ovrD3D11TextureData;
			ptr->Header = header->Native;
			ptr->pTexture = reinterpret_cast<ID3D11Texture2D*>(texture.ToPointer());
			ptr->pSRView = reinterpret_cast<ID3D11ShaderResourceView*>(srView.ToPointer());
		}

		~D3D11TextureData()
		{
			this->!D3D11TextureData();
		}

		!D3D11TextureData()
		{
			if (!undeletable) delete ptr;
		}

		property TextureHeader^ Header
		{
			TextureHeader^ get() { return gcnew TextureHeader(&(ptr->Header), true); }
			void set(TextureHeader^ value) { ptr->Header = value->Native; }
		}

		property IntPtr Texture
		{
			IntPtr get() { return (IntPtr)ptr->pTexture; }
			void set(IntPtr value) { ptr->pTexture = reinterpret_cast<ID3D11Texture2D*>(value.ToPointer()); }
		}

		property IntPtr SRView
		{
			IntPtr get() { return (IntPtr)ptr->pSRView; }
			void set(IntPtr value){ ptr->pSRView = reinterpret_cast<ID3D11ShaderResourceView*>(value.ToPointer()); }
		}

	internal:
		ovrD3D11TextureData* ptr;
		bool undeletable = false;

		D3D11TextureData(ovrD3D11TextureData* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrD3D11TextureData;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrD3D11TextureData Native
		{
			ovrD3D11TextureData get() { return *ptr; }
		}
	};

	public ref class D3D11Texture
	{
	public:
		D3D11Texture()
		{
			ptr = new ovrD3D11Texture;
		}

		D3D11Texture(Texture^ texture, D3D11TextureData^ d3d11)
		{
			ptr = new ovrD3D11Texture;
			ptr->Texture = texture->Native;
			ptr->D3D11 = d3d11->Native;
		}

		~D3D11Texture()
		{
			this->!D3D11Texture();
		}

		!D3D11Texture()
		{
			if (!undeletable) delete ptr;
		}

		property Texture^ Texture
		{
			OculusDK2NET::Texture^ get() { return gcnew OculusDK2NET::Texture(&(ptr->Texture), true); }
			void set(OculusDK2NET::Texture^ value) { ptr->Texture = value->Native; }
		}

		property D3D11TextureData^ D3D11
		{
			D3D11TextureData^ get() { return gcnew D3D11TextureData(&(ptr->D3D11), true); }
			void set(D3D11TextureData^ value){ ptr->D3D11 = value->Native; }
		}

	internal:
		ovrD3D11Texture* ptr;
		bool undeletable = false;

		D3D11Texture(ovrD3D11Texture* vi, bool undeletableFlag)
		{
			undeletable = undeletableFlag;
			if (undeletable)
			{
				ptr = vi;
			}
			else
			{
				ptr = new ovrD3D11Texture;
				memcpy(ptr, vi, sizeof(*vi));
			}
		}

		property ovrD3D11Texture Native
		{
			ovrD3D11Texture get() { return *ptr; }
		}
	};

	/// <summary>
	/// Wrapper class of Oculus SDK CAPI.
	/// </summary>
	public ref class OvrHmd
	{
	private:
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		OvrHmd()
		{

		}

		/// <summary>
		/// Destructor.
		/// </summary>
		~OvrHmd()
		{
		}

		/// <summary>
		/// Finalizer.
		/// </summary>
		!OvrHmd()
		{
		}

		/// <summary>
		/// Initializes all Oculus functionality. 
		/// </summary>
		static bool Initialize()
		{
			if (ovr_Initialize() != 0) return true;
			else return false;
		}

		/// <summary>
		/// Shuts down all Oculus functionality. 
		/// </summary>
		static void Shutdown()
		{
			ovr_Shutdown();
		}

		/// <summary>
		/// Returns version string representing libOVR version.
		/// </summary>
		String^ GetVersionString()
		{
			return gcnew String(ovr_GetVersionString());
		}

		/// <summary>
		/// Used to generate projection from ovrEyeDesc::Fov. 
		/// </summary>
		/// <param name="e"></param>
		static Matrix4f^ Matrix4f_Projection(FovPort^ fov, float znear, float zfar, bool rightHanded)
		{
			return gcnew Matrix4f(&ovrMatrix4f_Projection(fov->Native, znear, zfar, rightHanded), false);
		}

		/// <summary>
		/// Used for 2D rendering, Y is down orthoScale = 1.0f / pixelsPerTanAngleAtCenter orthoDistance = distance from camera, such as 0.8m. 
		/// </summary>
		/// <param name="e"></param>
		static Matrix4f^ Matrix4f_OrthoSubProjection(Matrix4f^ projection, Vector2f^ orthoScale, float orthoDistance, float eyeViewAdjustX)
		{
			return gcnew Matrix4f(&ovrMatrix4f_OrthoSubProjection(projection->Native, orthoScale->Native, orthoDistance, eyeViewAdjustX), false);
		}

		/// <summary>
		/// Returns global, absolute high-resolution time in seconds.
		/// </summary>
		static double GetTimeInSeconds()
		{
			return ovr_GetTimeInSeconds();
		}

		/// <summary>
		/// Waits until the specified absolute time. 
		/// </summary>
		static double WaitTillTime(double absTime)
		{
			return ovr_WaitTillTime(absTime);
		}

		/// <summary>
		/// Detects or re-detects HMDs and reports the total number detected.
		/// </summary>
		static int Detect()
		{
			return ovrHmd_Detect();
		}

		/// <summary>
		/// Creates a handle to an HMD which doubles as a description structure.
		/// </summary>
		static HmdDesc^ Create(int index)
		{
			return gcnew HmdDesc(ovrHmd_Create(index));
		}

		/// <summary>
		/// Destroy all Oculus functionality. 
		/// </summary>
		static void Destroy(HmdDesc^ hmd)
		{
			ovrHmd_Destroy(hmd->Native);
		}

		/// <summary>
		/// Creates a 'fake' HMD used for debugging only.
		/// </summary>
		static HmdDesc^ CreateDebug(HmdType type)
		{
			return gcnew HmdDesc(ovrHmd_CreateDebug((ovrHmdType)type));
		}

		/// <summary>
		/// Returns last error for HMD state. 
		/// </summary>
		static String^ GetLastError(HmdDesc^ hmd)
		{
			return gcnew String(ovrHmd_GetLastError(hmd->Native));
		}

		/// <summary>
		/// Platform specific function to specify the application window whose output will be displayed on the HMD.
		/// </summary>
		static bool AttachToWindow(HmdDesc^ hmd, IntPtr window, Recti^ destMirrorRect, Recti^ sourceRenderTargetRect)
		{
			return ovrHmd_AttachToWindow(hmd->Native, (void*)window, destMirrorRect == nullptr ? nullptr : &destMirrorRect->Native, sourceRenderTargetRect == nullptr ? nullptr : &sourceRenderTargetRect->Native) != 0 ? true : false;
		}

		/// <summary>
		/// Returns capability bits that are enabled at this time as described by ovrHmdCaps.
		/// </summary>
		static HmdCaps GetEnabledCaps(HmdDesc^ hmd)
		{
			return (HmdCaps)ovrHmd_GetEnabledCaps(hmd->Native);
		}

		/// <summary>
		/// Modifies capability bits described by ovrHmdCaps that can be modified, such as ovrHmdCap_LowPersistance.
		/// </summary>
		static void SetEnabledCaps(HmdDesc^ hmd, HmdCaps hmdCaps)
		{
			ovrHmd_SetEnabledCaps(hmd->Native, (ovrHmdCaps)hmdCaps);
		}

		/// <summary>
		/// All tracking interface functions are thread-safe, allowing tracking state to be sampled from different threads.
		/// </summary>
		static bool ConfigureTracking(HmdDesc^ hmd, TrackingCaps supportedTrackingCaps, TrackingCaps requiredTrackingCaps)
		{
			return ovrHmd_ConfigureTracking(hmd->Native, (ovrTrackingCaps)supportedTrackingCaps, (ovrTrackingCaps)requiredTrackingCaps) != 0 ? true : false;
		}

		/// <summary>
		/// Re-centers the sensor orientation.
		/// </summary>
		static void RecenterPose(HmdDesc^ hmd)
		{
			ovrHmd_RecenterPose(hmd->Native);
		}

		/// <summary>
		/// Returns tracking state reading based on the specified absolute system time.
		/// </summary>
		static TrackingState^ GetTrackingState(HmdDesc^ hmd, double absTime)
		{
			return gcnew TrackingState(&ovrHmd_GetTrackingState(hmd->Native, absTime), false);
		}

		/// <summary>
		/// Calculates the recommended texture size for rendering a given eye within the HMD with a given FOV cone.
		/// </summary>
		static Sizei^ GetFovTextureSize(HmdDesc^ hmd, EyeType eye, FovPort^ fov, float pixelsPerDisplayPixel)
		{
			return gcnew Sizei(&ovrHmd_GetFovTextureSize(hmd->Native, (ovrEyeType)eye, fov->Native, pixelsPerDisplayPixel), false);
		}

		/// <summary>
		/// Configures rendering and fills in computed render parameters.
		/// </summary>
		static bool ConfigiureRendering(HmdDesc^ hmd, GLConfig^ apiConfig, DistortionCaps distortionCaps, array<FovPort^>^ eyeFovIn, [Runtime::InteropServices::Out] array<EyeRenderDesc^>^% eyeRenderDescOut)
		{
			ovrGLConfig cfg = apiConfig->Native;
			
			ovrFovPort eyeFovInNative[2];
			eyeFovInNative[0] = eyeFovIn[0]->Native;
			eyeFovInNative[1] = eyeFovIn[1]->Native;

			ovrEyeRenderDesc eyeRenderDescOutNative[2];

			bool result = ovrHmd_ConfigureRendering(hmd->Native, &cfg.Config, (unsigned int)distortionCaps, eyeFovInNative, eyeRenderDescOutNative) != 0 ? true : false;

			eyeRenderDescOut = gcnew array<EyeRenderDesc^>(2);
			eyeRenderDescOut[0] = gcnew EyeRenderDesc(&eyeRenderDescOutNative[0], false);
			eyeRenderDescOut[1] = gcnew EyeRenderDesc(&eyeRenderDescOutNative[1], false);

			return result;
		}

		/// <summary>
		/// Begins a frame, returning timing information.
		/// </summary>
		static FrameTiming^ BeginFrame(HmdDesc^ hmd, unsigned int frameIndex)
		{
			return gcnew FrameTiming(&ovrHmd_BeginFrame(hmd->Native, frameIndex), false);
		}

		/// <summary>
		/// Ends a frame, submitting the rendered textures to the frame buffer.
		/// </summary>
		static void EndFrame(HmdDesc^ hmd, array<Posef^>^ renderPose, array<GLTexture^>^ eyeTexture)
		{
			ovrPosef renderPoseNative[2];
			renderPoseNative[0] = renderPose[0]->Native;
			renderPoseNative[1] = renderPose[1]->Native;

			ovrGLTexture eyeTextureNative[2];
			eyeTextureNative[0] = eyeTexture[0]->Native;
			eyeTextureNative[1] = eyeTexture[1]->Native;

			ovrHmd_EndFrame(hmd->Native, (ovrPosef*)(&renderPoseNative[0]), (ovrTexture*)(&eyeTextureNative[0]));
		}

		/// <summary>
		/// Returns predicted head pose in outHmdTrackingState and offset eye poses in outEyePoses as an atomic operation.
		/// </summary>
		static void GetEyePoses(HmdDesc^ hmd, unsigned int frameIndex, array<Vector3f^>^ hmdToEyeViewOffset, [Runtime::InteropServices::Out] array<Posef^>^% eyePoses, [Runtime::InteropServices::Out] TrackingState^% hmdTrackingState)
		{
			ovrVector3f hmdToEyeViewOffsetNative[2];
			hmdToEyeViewOffsetNative[0] = hmdToEyeViewOffset[0]->Native;
			hmdToEyeViewOffsetNative[1] = hmdToEyeViewOffset[1]->Native;

			ovrPosef outEyePoses[2];
			ovrTrackingState outHmdTrackingState;

			ovrHmd_GetEyePoses(hmd->Native, frameIndex, hmdToEyeViewOffsetNative, outEyePoses, &outHmdTrackingState);

			eyePoses[0] = gcnew Posef(&outEyePoses[0], false);
			eyePoses[1] = gcnew Posef(&outEyePoses[1], false);

			hmdTrackingState = gcnew TrackingState(&outHmdTrackingState, false);
		}

		/// <summary>
		/// DEPRECATED: Prefer using ovrHmd_GetEyePoses instead Function was previously called ovrHmd_GetEyePose Returns the predicted head pose to use when rendering the specified eye. 
		/// </summary>
		static Posef^ GetHmdPosePerEye(HmdDesc^ hmd, EyeType eye)
		{
			return gcnew Posef(&ovrHmd_GetHmdPosePerEye(hmd->Native, (ovrEyeType)eye), false);
		}

		/// <summary>
		/// Computes the distortion viewport, view adjust, and other rendering parameters for the specified eye.
		/// </summary>
		static EyeRenderDesc^ GetRenderDesc(HmdDesc^ hmd, EyeType eyeType, FovPort^ fov)
		{
			return gcnew EyeRenderDesc(&ovrHmd_GetRenderDesc(hmd->Native, (ovrEyeType)eyeType, fov->Native), false);
		}

		/// <summary>
		/// Generate distortion mesh per eye.
		/// </summary>
		static bool CreateDistortionMesh(HmdDesc^ hmd, EyeType eyeType, FovPort^ fov, DistortionCaps distortionCaps, [Runtime::InteropServices::Out] DistortionMesh^% meshData)
		{
			ovrDistortionMesh meshDataNative;

			bool result = ovrHmd_CreateDistortionMesh(hmd->Native, (ovrEyeType)eyeType, fov->Native, (unsigned int)distortionCaps, &meshDataNative) != 0 ? true : false;

			meshData = gcnew DistortionMesh();
			meshData->IndexCount = meshDataNative.IndexCount;
			System::Collections::Generic::List<unsigned short>^ indexData = gcnew System::Collections::Generic::List<unsigned short>(meshData->IndexCount);
			for (unsigned int i = 0; i < meshData->IndexCount; i++)
			{
				indexData->Add(meshDataNative.pIndexData[i]);
			}
			meshData->IndexData = indexData;

			meshData->VertexCount = meshDataNative.VertexCount;
			System::Collections::Generic::List<DistortionVertex^>^ vertexData = gcnew System::Collections::Generic::List<DistortionVertex^>(meshData->VertexCount);
			for (unsigned int i = 0; i < meshData->VertexCount; i++)
			{
				vertexData->Add(gcnew DistortionVertex(&meshDataNative.pVertexData[i], false));
			}
			meshData->VertexData = vertexData;

			return result;
		}

		/// <summary>
		/// Used to free the distortion mesh allocated by ovrHmd_GenerateDistortionMesh.
		/// </summary>
		static void DestroyDistortionMesh(DistortionMesh^% meshData)
		{
			ovrHmd_DestroyDistortionMesh(&(meshData->Native));
			meshData->~DistortionMesh();
		}

		/// <summary>
		/// Computes updated 'uvScaleOffsetOut' to be used with a distortion if render target size or viewport changes after the fact.
		/// </summary>
		static void GetRenderScaleAndOffset(FovPort^ fov, Sizei^ textureSize, Recti^ renderViewport, array<Vector2f^>^ uvScaleOffsetOut)
		{
			ovrVector2f uvScaleOffsetOutNative[2];			
			ovrHmd_GetRenderScaleAndOffset(fov->Native, textureSize->Native, renderViewport->Native, uvScaleOffsetOutNative);
			
			uvScaleOffsetOut[0] = gcnew Vector2f(&uvScaleOffsetOutNative[0], false);
			uvScaleOffsetOut[1] = gcnew Vector2f(&uvScaleOffsetOutNative[1], false);
		}

		/// <summary>
		/// Thread-safe timing function for the main thread.
		/// </summary>
		static FrameTiming^ GetFrameTiming(HmdDesc^ hmd, unsigned int frameIndex)
		{
			return gcnew FrameTiming(&ovrHmd_GetFrameTiming(hmd->Native, frameIndex), false);
		}

		/// <summary>
		/// Called at the beginning of the frame on the rendering thread.
		/// </summary>
		static FrameTiming^ BeginFrameTiming(HmdDesc^ hmd, unsigned int frameIndex)
		{
			return gcnew FrameTiming(&ovrHmd_BeginFrame(hmd->Native, frameIndex), false);
		}

		/// <summary>
		/// Marks the end of client distortion rendered frame, tracking the necessary timing information.
		/// </summary>
		static void EndFrameTiming(HmdDesc^ hmd)
		{
			ovrHmd_EndFrameTiming(hmd->Native);
		}

		/// <summary>
		/// Initializes and resets frame time tracking.
		/// </summary>
		static void ResetFrameTiming(HmdDesc^ hmd, unsigned int frameIndex)
		{
			ovrHmd_ResetFrameTiming(hmd->Native, frameIndex);
		}

		/// <summary>
		/// Computes timewarp matrices used by distortion mesh shader, these are used to adjust for head orientation change since the last call to ovrHmd_GetEyePoses when rendering this eye.
		/// </summary>
		static void GetEyeTimewarpMatrices(HmdDesc^ hmd, EyeType eye, Posef^ renderPose, array<Matrix4f^>^ twmOut)
		{
			ovrMatrix4f twmOutNative[2];
			ovrHmd_GetEyeTimewarpMatrices(hmd->Native, (ovrEyeType)eye, renderPose->Native, twmOutNative);

			twmOut[0] = gcnew Matrix4f(&twmOutNative[0], false);
			twmOut[1] = gcnew Matrix4f(&twmOutNative[1], false);
		}

		/// <summary>
		/// Does latency test processing and returns 'TRUE' if specified rgb color should be used to clear the screen.
		/// </summary>
		static bool ProcessLatencyTest(HmdDesc^ hmd, [Runtime::InteropServices::Out] System::Drawing::Color^% outColor)
		{
			unsigned char col[3];
			bool result = ovrHmd_ProcessLatencyTest(hmd->Native, col) != 0 ? true : false;
			
			outColor = gcnew System::Drawing::Color();
			outColor = System::Drawing::Color::FromArgb(col[0], col[1], col[2]);

			return result;
		}

		/// <summary>
		/// Returns the latency testing color in rgbColorOut to render when using a DK2 Returns false if this feature is disabled or not-applicable (e.g. using a DK1)
		/// </summary>
		static bool GetLatencyTest2DrawColor(HmdDesc^ hmddesc, [Runtime::InteropServices::Out] array<unsigned char>^ rgbColor)
		{
			unsigned char rgbColorOut[3];

			bool result = ovrHmd_GetLatencyTest2DrawColor(hmddesc->Native, rgbColorOut) != 0 ? true : false;

			rgbColor = gcnew array<unsigned char>(3);
			rgbColor[0] = rgbColorOut[0];
			rgbColor[1] = rgbColorOut[1];
			rgbColor[2] = rgbColorOut[2];

			return result;
		}

		/// <summary>
		/// Returns non-null string once with latency test result, when it is available.
		/// </summary>
		static String^ GetLatencyTestResult(HmdDesc^ hmd)
		{
			return gcnew String(ovrHmd_GetLatencyTestResult(hmd->Native));
		}

		/// <summary>
		/// Returns the current state of the HSW display. 
		/// </summary>
		static void GetHSWDisplayState(HmdDesc^ hmd, HswDisplayState^% hasWarningState)
		{
			ovrHSWDisplayState state;
			ovrHmd_GetHSWDisplayState(hmd->Native, &state);

			hasWarningState = gcnew HswDisplayState(&state, false);
		}

		/// <summary>
		/// Returns non-null string once with latency test result, when it is available.
		/// </summary>
		static bool DismissHSWDisplay(HmdDesc^ hmd)
		{
			return ovrHmd_DismissHSWDisplay(hmd->Native) != 0 ? true : false;
		}

		/// <summary>
		/// Get boolean property.
		/// </summary>
		static bool GetBool(HmdDesc^ hmd, String^ propertyName, bool defaultVal)
		{
			return ovrHmd_GetBool(hmd->Native, marshal_as<std::string>(propertyName).c_str(), defaultVal) != 0 ? true : false;
		}

		/// <summary>
		/// Modify bool property; false if property doesn't exist or is readonly. 
		/// </summary>
		static bool SetBool(HmdDesc^ hmd, String^ propertyName, bool value)
		{
			return ovrHmd_SetBool(hmd->Native, marshal_as<std::string>(propertyName).c_str(), (ovrBool)value) != 0 ? true : false;
		}

		/// <summary>
		/// Get integer property.
		/// </summary>
		static int GetInt(HmdDesc^ hmd, String^ propertyName, int defaultVal)
		{
			return ovrHmd_GetInt(hmd->Native, marshal_as<std::string>(propertyName).c_str(), defaultVal);
		}

		/// <summary>
		/// Modify integer property; false if property doesn't exist or is readonly.
		/// </summary>
		static bool SetInt(HmdDesc^ hmd, String^ propertyName, int value)
		{
			return ovrHmd_SetInt(hmd->Native, marshal_as<std::string>(propertyName).c_str(), value) != 0 ? true :false;
		}

		/// <summary>
		/// Get float property.
		/// </summary>
		static float GetFloat(HmdDesc^ hmd, String^ propertyName, float defaultVal)
		{
			return ovrHmd_GetFloat(hmd->Native, marshal_as<std::string>(propertyName).c_str(), defaultVal);
		}

		/// <summary>
		/// Modify float property; false if property doesn't exist or is readonly. 
		/// </summary>
		static bool SetFloat(HmdDesc^ hmd, String^ propertyName, float value)
		{
			return ovrHmd_SetFloat(hmd->Native, marshal_as<std::string>(propertyName).c_str(), value) != 0 ? true : false;
		}

		/// <summary>
		/// Get float[] property.
		/// </summary>
		static unsigned int GetFloatArray(HmdDesc^ hmd, String^ propertyName, cli::array<float>^ values, unsigned int arraySize)
		{
			pin_ptr<float> v = &values[0];
			return ovrHmd_GetFloatArray(hmd->Native, marshal_as<std::string>(propertyName).c_str(), v, values->Length);
		}

		/// <summary>
		/// Modify float[] property; false if property doesn't exist or is readonly. 
		/// </summary>
		static bool SetFloatArray(HmdDesc^ hmd, String^ propertyName, cli::array<float>^ values, unsigned int arraySize)
		{
			pin_ptr<float> v = &values[0];
			return ovrHmd_SetFloatArray(hmd->Native, marshal_as<std::string>(propertyName).c_str(), v, values->Length) != 0 ? true :false;
		}

		/// <summary>
		/// Get string property.
		/// </summary>
		static String^ HmdGetString(HmdDesc^ hmd, String^ propertyName, String^ defaultVal)
		{
			return gcnew String(ovrHmd_GetString(hmd->Native, marshal_as<std::string>(propertyName).c_str(), marshal_as<std::string>(defaultVal).c_str()));
		}

		/// <summary>
		/// Set string property. 
		/// </summary>
		static bool HmdSetString(HmdDesc^ hmd, String^ propertyName, String^ value)
		{
			return ovrHmd_SetString(hmd->Native, marshal_as<std::string>(propertyName).c_str(), marshal_as<std::string>(value).c_str()) != 0 ? true : false;
		}


	};
}
