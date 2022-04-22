#include<iostream>
#include"NVAPI/nvapi.h"
#include"NVAPI/nvapi_lite_common.h"

#if _M_AMD64
#pragma comment(lib,"NVAPI/amd64/nvapi64.lib")
#else
#pragma comment(lib,"NVAPI/x86/nvapi.lib")
#endif

NvAPI_ShortString err;

int main()
{
	NvAPI_Status ret = NVAPI_OK;

	ret = NvAPI_Initialize();

	if (ret != NVAPI_OK)
	{
		NvAPI_GetErrorMessage(ret, err);
		std::cout << "NVAPI NvAPI_Initialize: " << err << std::endl;
	}

	//Show NVAPI version
	NvAPI_ShortString ver;
	NvAPI_GetInterfaceVersionString(ver);
	std::cout << "NVAPI Version: " << ver << std::endl;
	
	//Show display driver version
	NvU32 dd_ver;
	NvAPI_ShortString branch;
	ret = NvAPI_SYS_GetDriverAndBranchVersion(&dd_ver, branch);
	std::cout << "Display driver version: " << dd_ver << std::endl;


	//Show GPU name
	NvU32 cnt;
	NvPhysicalGpuHandle phys;
	ret = NvAPI_EnumPhysicalGPUs(&phys, &cnt);
	NvAPI_ShortString GPUName;
	ret = NvAPI_GPU_GetFullName(phys, GPUName);
	if (ret != NVAPI_OK)
	{
		NvAPI_GetErrorMessage(ret, err);
		std::cout << "NVAPI NvAPI_Initialize: " << err << std::endl;
	}
	else
	{
		std::cout << "Name: " << GPUName << std::endl;
	}
	
	//Show attached GPU nums
	NvPhysicalGpuHandle hGPUHandles[NVAPI_MAX_PHYSICAL_GPUS] = { 0 };
	NvU32 cnt_attached = 0;
	ret = NvAPI_EnumPhysicalGPUs(hGPUHandles, &cnt_attached);
	if (ret != NVAPI_OK)
	{
		NvAPI_GetErrorMessage(ret, err);
		std::cout << "NVAPI NvAPI_Initialize: " << err << std::endl;
	}
	else
	{
		std::cout << "Attached: " << cnt_attached << std::endl;
	}

	//Show GPU temp
	NV_GPU_THERMAL_SETTINGS thermal;
	thermal.version = NV_GPU_THERMAL_SETTINGS_VER;
	ret = NvAPI_GPU_GetThermalSettings(phys, 0, &thermal);
	if (ret != NVAPI_OK)
	{
		NvAPI_GetErrorMessage(ret, err);
		std::cout << "NVAPI NvAPI_Initialize: " << err << std::endl;
	}
	else
	{
		std::cout << "Temp: " << thermal.sensor[0].currentTemp << std::endl;
	}


	return 0;
}