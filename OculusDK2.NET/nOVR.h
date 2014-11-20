//Main DLL file

#pragma once

//Oculus SDK 0.4.x
#include "OVR.h"


#ifdef _DEBUG
#pragma comment(lib, "./LibOVR/Lib/Win32/VS2010/libovrd.lib")
#else
#pragma comment(lib, "./LibOVR/Lib/Win32/VS2010/libovr.lib")
#endif

//Additional lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Gdi32.lib")


using namespace System;

class nOvr
{
	ovrHmd hmd;
	
	ovrHmdType type;
	const char* productName;
	const char* manufacture;
	short vendorId;
	short productId;
	char* serialNumber;
	short firmwareMajor;
	short firmwareMinor;
	float cameraFrustumHFovInRadians;
	float cameraFrustumVFovInRadians;
	float cameraFrustumNearZInMeters;
	float cameraFrustumFarZInMeters;
	unsigned int hmdCaps;
	unsigned int trackingCaps;
	unsigned int distortionCaps;
	ovrSizei resolution;
	ovrVector2i windowsPos;
	ovrFovPort defaultEyeFov[ovrEye_Count];
	ovrFovPort maxEyeFov[ovrEye_Count];
	ovrEyeType eyeRenderOrder[ovrEye_Count];
	const char* displayDeviceName;
	int displayId;

public:
	///
	/// コンストラクタ
	///
	nOvr()
	{
	}

	///
	/// デストラクタ
	///
	~nOvr()
	{
	}

	///
	/// HMDの初期化
	///
	int Open()
	{
		ovr_Initialize();

		hmd = ovrHmd_Create(0);

		if (hmd)
		{
			// HMDの詳細を取得
			type = hmd->Type;
			productName = hmd->ProductName;
			manufacture = hmd->Manufacturer;
			vendorId = hmd->VendorId;
			productId = hmd->ProductId;
			strcpy(serialNumber, hmd->SerialNumber);
			firmwareMajor = hmd->FirmwareMajor;
			firmwareMinor = hmd->FirmwareMinor;
			cameraFrustumHFovInRadians = hmd->CameraFrustumHFovInRadians;
			cameraFrustumVFovInRadians = hmd->CameraFrustumVFovInRadians;
			cameraFrustumNearZInMeters = hmd->CameraFrustumNearZInMeters;
			cameraFrustumFarZInMeters = hmd->CameraFrustumFarZInMeters;
			hmdCaps = hmd->HmdCaps;
			trackingCaps = hmd->TrackingCaps;
			resolution = hmd->Resolution;
			windowsPos = hmd->WindowsPos;
			for (int i = 0; i < ovrEye_Count; i++)
			{
				defaultEyeFov[i] = hmd->DefaultEyeFov[i];
				maxEyeFov[i] = hmd->MaxEyeFov[i];
				eyeRenderOrder[i] = hmd->EyeRenderOrder[i];
			}
			displayDeviceName = hmd->DisplayDeviceName;
			displayId = hmd->DisplayId;
		}

		return 0;
	}

	///
	/// HMDの終了
	///
	void Close()
	{
		ovrHmd_Destroy(hmd);
		ovr_Shutdown();
	}
};
