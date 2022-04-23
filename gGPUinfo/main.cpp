#include<iostream>
#include"NVAPI/nvapi.h"
#include"nvml/nvml.h"

//#if _M_AMD64
//#pragma comment(lib,"NVAPI/amd64/nvapi64.lib")
//#else
//#pragma comment(lib,"NVAPI/x86/nvapi.lib")
//#endif

#pragma comment(lib,"nvml/lib/nvml.lib")

const unsigned int gpu_id = 0;

int main()
{
	nvmlInit();

	nvmlDevice_t device;

	nvmlReturn_t result;

	nvmlDeviceGetHandleByIndex(gpu_id, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to initialize NVML: " << nvmlErrorString(result) << std::endl;
	}

	//Attached GPU count
	unsigned int device_count;
	result = nvmlDeviceGetCount(&device_count);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get device count: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << "Count: " << device_count << std::endl;
	}


	//GPU name
	char device_name[64];
	result = nvmlDeviceGetName(device, device_name, 64);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get device name: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << "Name: " << device_name << std::endl;
	}


	//NVML version
	char nvml_ver[64];
	result = nvmlSystemGetNVMLVersion(nvml_ver, 64);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get NVML version: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << "NVML version: " << nvml_ver << std::endl;
	}



	//Driver version
	char driver_ver[64];
	result = nvmlSystemGetDriverVersion(driver_ver, 64);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get driver version: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << "Driver version: " << driver_ver << std::endl;
	}







	//Fan speed
	unsigned int device_fanspeed;
	result = nvmlDeviceGetFanSpeed(device, &device_fanspeed);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get fan speed: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << device_fanspeed << std::endl;
	}

	return 0;
}