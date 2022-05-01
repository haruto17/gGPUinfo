#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<windows.h>
#include<time.h>
#include"nvml/nvml.h"

#pragma comment(lib,"nvml/lib/nvml.lib")

const unsigned int gpu_id = 0;



std::string GetTimeStamp()
{
	time_t now = time(NULL);
	struct tm local;
	errno_t err = localtime_s(&local, &now);

	std::vector<int> timeInfo(6);

	timeInfo[0] = local.tm_year + 1900;
	timeInfo[1] = local.tm_mon + 1;
	timeInfo[2] = local.tm_mday;
	timeInfo[3] = local.tm_hour;
	timeInfo[4] = local.tm_min;
	timeInfo[5] = local.tm_sec;

	std::string timestamp = std::to_string(timeInfo[0]);

	for (int i = 1; i < 6; i++)
	{

		timestamp += "/" + std::to_string(timeInfo[i]);
	}

	return timestamp;

}

unsigned int GetDeviceAttached()
{
	nvmlReturn_t result;
	unsigned int count;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetCount(&count);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return count;
	}
}

std::string GetDeviceName(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	char device_name[64];

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	//If you specify an invalid index...
	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetName(device, device_name, 64);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return device_name;
	}
}


std::string GetNVMLVersion()
{
	nvmlReturn_t result;
	char ver[64];

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlSystemGetNVMLVersion(ver, 64);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return ver;
	}
}


std::string GetDriverVersion()
{
	nvmlReturn_t result;
	char ver[64];

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlSystemGetDriverVersion(ver, 64);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return ver;
	}
}


std::string GetCUDAVersion()
{
	nvmlReturn_t result;
	int ver;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlSystemGetCudaDriverVersion(&ver);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		int ver_major = NVML_CUDA_DRIVER_VERSION_MAJOR(ver);
		int ver_minor = NVML_CUDA_DRIVER_VERSION_MINOR(ver);
		std::string s_ver;
		s_ver += std::to_string(ver_major);
		s_ver += ".";
		s_ver += std::to_string(ver_minor);

		return s_ver;
	}
}


unsigned int GetDevicePowerUsage(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	unsigned int power;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}


	result = nvmlDeviceGetPowerUsage(device, &power);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return power;
	}
}


float GetDeviceTemperature(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	unsigned int temp;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		float f_temp = float(temp);
		return f_temp;
	}
}


//unsigned int GetDeviceFanSpeed(int index)
//{
//	nvmlDevice_t device;
//	nvmlReturn_t result;
//	unsigned int fanspeed;
//
//	result = nvmlInit();
//	if (NVML_SUCCESS != result)
//	{
//		std::cout << nvmlErrorString(result) << std::endl;
//		exit(EXIT_FAILURE);
//	}
//
//	result = nvmlDeviceGetHandleByIndex(index, &device);
//	if (NVML_SUCCESS != result)
//	{
//		std::cout << nvmlErrorString(result) << std::endl;
//		exit(EXIT_FAILURE);
//	}
//
//	result = nvmlDeviceGetFanSpeed(device, &fanspeed);
//	if (NVML_SUCCESS != result)
//	{
//		std::cout << nvmlErrorString(result) << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	else
//	{
//		return fanspeed;
//	}
//}


unsigned int GetDeviceGPUUtil(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	nvmlUtilization_t util;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetUtilizationRates(device, &util);

	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return util.gpu;
	}
}


unsigned int GetDeviceMemoryUtil(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	nvmlUtilization_t util;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetUtilizationRates(device, &util);

	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return util.memory;
	}
}


unsigned int GetDeviceMemoryFree(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	nvmlMemory_t memory;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetMemoryInfo(device, &memory);

	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return memory.free;
	}
}


unsigned int GetDeviceMemoryUsed(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	nvmlMemory_t memory;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetMemoryInfo(device, &memory);

	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return memory.used;
	}
}


unsigned int GetDeviceMemoryTotal(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	nvmlMemory_t memory;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetMemoryInfo(device, &memory);

	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return memory.total;
	}
}


unsigned int GetDeviceClock(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	unsigned int clock;

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetClock(device, NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CURRENT, &clock);
	
	if (NVML_SUCCESS != result)
	{
		std::cout << nvmlErrorString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return clock;
	}
}


int main()
{
	nvmlInit();

	//Get Attached GPUs
	unsigned int device_count = GetDeviceAttached();
	std::cout << "Attached: " << device_count << std::endl;
	

	//Get GPU name
	std::string device_name = GetDeviceName(0);
	std::cout << "Name: " << device_name << std::endl;


	//Get NVML version
	std::string nvml_ver = GetNVMLVersion();
	std::cout << "NVML version: " << nvml_ver << std::endl;


	//Get driver version
	std::string driver_ver = GetDriverVersion();
	std::cout << "Driver version: " << driver_ver << std::endl;


	//Get CUDA version
	std::string cuda_ver = GetCUDAVersion();
	std::cout << "CUDA version: " << cuda_ver << std::endl;


	std::cout << std::endl;


	while (true)
	{

		//Show timestamp
		std::cout << GetTimeStamp() << std::endl;


		//Get power util
		unsigned int device_power = GetDevicePowerUsage(0);
		std::cout << "Power util: " << device_power / 1000.0 << "[W]" << std::endl;


		//Get temperature
		float device_temp = GetDeviceTemperature(0);
		std::cout << "Temp: " << device_temp << "[C]" << std::endl;


		////Get fan speed
		//unsigned int device_fanspeed = GetDeviceFanSpeed(0);
		//std::cout << "Fan speed: " << device_fanspeed << "[%]" << std::endl;


		//Get GPU util
		unsigned int gpu_util = GetDeviceGPUUtil(0);
		std::cout << "GPU util: " << gpu_util << "[%]" << std::endl;


		//Get memory util
		unsigned int memory_util = GetDeviceMemoryUtil(0);
		std::cout << "Memory util: " << memory_util << "[%]" << std::endl;


		//Get memory free
		unsigned int memory_free = GetDeviceMemoryFree(0);
		std::cout << "Memory free: " << memory_free << "[B]" << std::endl;


		//Get memory used
		unsigned int memory_used = GetDeviceMemoryUsed(0);
		std::cout << "Memory used: " << memory_used << "[B]" << std::endl;


		//Get memory total
		unsigned int memory_total = GetDeviceMemoryTotal(0);
		std::cout << "Memory total: " << memory_total << "[B]" << std::endl;


		//Get clock;
		unsigned int device_clock = GetDeviceClock(0);
		std::cout << "Clock: " << device_clock << "[MHz]" << std::endl;

		std::cout << std::endl;

		Sleep(5000);
	}
	
	nvmlShutdown();

}