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
		std::cout << "Failed to query device count: " << nvmlErrorString(result) << std::endl;
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
		std::cout << "Failed to query device name: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << "Name: " << device_name << std::endl;
	}

	return 0;
}