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
	
	NvU32 cnt;

	NvPhysicalGpuHandle phys;

	ret = NvAPI_EnumPhysicalGPUs(&phys, &cnt);

	//Show GPU name
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

	////Get timestamp
	//system("nvidia-smi --query-gpu=timestamp --format=csv");

	//std::cout << std::endl;

	////Get connected GPUs
	//system("nvidia-smi --query-gpu=count --format=csv");

	//std::cout << std::endl;

	////Get GPU name
	//system("nvidia-smi --query-gpu=gpu_name --format=csv");

	//std::cout << std::endl;

	////Get driver_version
	//system("nvidia-smi --query-gpu=driver_version --format=csv");

	//std::cout << std::endl;

	////Get vbios_version
	//system("nvidia-smi --query-gpu=vbios_version --format=csv");

	//std::cout << std::endl;

	////Get GPU power consumption
	//system("nvidia-smi --query-gpu=power.draw --format=csv");

	//std::cout << std::endl;

	////Get GPU temperature
	//system("nvidia-smi --query-gpu=temperature.gpu --format=csv");

	//std::cout << std::endl;

	////Get GPU fan speed
	//system("nvidia-smi --query-gpu=fan.speed --format=csv");

	//std::cout << std::endl;

	////Get GPU graphics clocks
	//system("nvidia-smi --query-gpu=clocks.gr --format=csv");

	//std::cout << std::endl;

	////Get GPU memory clocks
	//system("nvidia-smi --query-gpu=clocks.sm --format=csv");

	//std::cout << std::endl;

	////Get GPU utilization
	//system("nvidia-smi --query-gpu=utilization.gpu --format=csv");

	//std::cout << std::endl;

	////Get GPU memory utilization
	//system("nvidia-smi --query-gpu=utilization.memory --format=csv");

	//std::cout << std::endl;

	////Get total GPU memory
	//system("nvidia-smi --query-gpu=memory.total --format=csv");

	//std::cout << std::endl;

	////Get free GPU memory
	//system("nvidia-smi --query-gpu=memory.free --format=csv");

	//std::cout << std::endl;

	////Get used GPU memory
	//system("nvidia-smi --query-gpu=memory.used --format=csv");

	////Show all GPU infomation :)
	//system("nvidia-smi -i 0 -q");

	return 0;
}