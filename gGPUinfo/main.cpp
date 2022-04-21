#include<iostream>
#include"NVAPI/nvapi.h"

#if _M_AMD64
#pragma comment(lib,"NVAPI/amd64/nvapi64.lib")
#else
#pragma comment(lib,"NVAPI/x86/nvapi.lib")
#endif

int main()
{

	NvAPI_Status nStatus = NvAPI_Initialize();
	
	//Get connected GPU num
	if (nStatus == NVAPI_OK)
	{
		NvPhysicalGpuHandle hGPUHandles[NVAPI_MAX_PHYSICAL_GPUS] = { 0 };
		
		NvU32 count = 0;

		nStatus = NvAPI_EnumPhysicalGPUs(hGPUHandles, &count);

		if (nStatus == NVAPI_OK)
		{
			std::cout << count << std::endl;
		}
		else
		{
			std::cout << nStatus << std::endl;
		}
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