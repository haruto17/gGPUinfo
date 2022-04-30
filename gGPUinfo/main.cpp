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
		return NULL;
	}

	result = nvmlDeviceGetCount(&count);
	if (NVML_SUCCESS != result)
	{
		return NULL;
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

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		exit(EXIT_FAILURE);
	}

	result = nvmlDeviceGetName(device, device_name, 64);
	if (NVML_SUCCESS != result)
	{
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
		exit(EXIT_FAILURE);
	}

	result = nvmlSystemGetNVMLVersion(ver, 64);
	if (NVML_SUCCESS != result)
	{
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
		exit(EXIT_FAILURE);
	}

	result = nvmlSystemGetDriverVersion(ver, 64);
	if (NVML_SUCCESS != result)
	{
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
		exit(EXIT_FAILURE);
	}

	result = nvmlSystemGetCudaDriverVersion(&ver);
	if (NVML_SUCCESS != result)
	{
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

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}

	result = nvmlDeviceGetPowerUsage(device, &power);
	if (NVML_SUCCESS != result)
	{
		return NULL;
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

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}

	result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}
	else
	{
		float f_temp = float(temp);
		return f_temp;
	}
}


unsigned int GetDeviceFanSpeed(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	unsigned int fanspeed;

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}

	result = nvmlDeviceGetFanSpeed(device, &fanspeed);
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}
	else
	{
		return fanspeed;
	}
}


unsigned int GetDeviceGPUUtil(int index)
{
	nvmlDevice_t device;
	nvmlReturn_t result;
	nvmlUtilization_t util;

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}

	result = nvmlDeviceGetUtilizationRates(device, &util);

	if (NVML_SUCCESS != result)
	{
		return NULL;
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

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}

	result = nvmlDeviceGetUtilizationRates(device, &util);

	if (NVML_SUCCESS != result)
	{
		return NULL;
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

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}

	result = nvmlDeviceGetMemoryInfo(device, &memory);

	if (NVML_SUCCESS != result)
	{
		return NULL;
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

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}

	result = nvmlDeviceGetMemoryInfo(device, &memory);

	if (NVML_SUCCESS != result)
	{
		return NULL;
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

	nvmlDeviceGetHandleByIndex(index, &device);

	result = nvmlInit();
	if (NVML_SUCCESS != result)
	{
		return NULL;
	}

	result = nvmlDeviceGetMemoryInfo(device, &memory);

	if (NVML_SUCCESS != result)
	{
		return NULL;
	}
	else
	{
		return memory.total;
	}
}


int main()
{
	nvmlInit();

	//Get Attached GPUs
	unsigned int device_count = GetDeviceAttached();
	if (device_count == NULL)
	{
		std::cout << "Failed to query get device count" << std::endl;
	}
	else
	{
		std::cout << "Attached: " << device_count << std::endl;
	}

	//Get GPU name
	std::string device_name = GetDeviceName(0);
	std::cout << device_name << std::endl;


	//Get NVML version
	std::string nvml_ver = GetNVMLVersion();
	std::cout << nvml_ver << std::endl;


	//Get driver version
	std::string driver_ver = GetDriverVersion();
	std::cout << driver_ver << std::endl;


	//Get CUDA version
	std::string cuda_ver = GetCUDAVersion();
	std::cout << cuda_ver << std::endl;


	std::cout << std::endl;


	while (true)
	{

		//Show timestamp
		std::cout << GetTimeStamp() << std::endl;


		//Get power util
		unsigned int device_power = GetDevicePowerUsage(0);
		std::cout << device_power / 1000.0 << "[W]" << std::endl;


		//Get temperature
		float device_temp = GetDeviceTemperature(0);
		std::cout << device_temp << "[C]" << std::endl;


		//Get fan speed
		unsigned int device_fanspeed = GetDeviceFanSpeed(0);
		std::cout << device_fanspeed << std::endl;


		//Get GPU util
		unsigned int gpu_util = GetDeviceGPUUtil(0);
		std::cout << gpu_util << "[%]" << std::endl;


		//Get memory util
		unsigned int memory_util = GetDeviceMemoryUtil(0);
		std::cout << memory_util << "[%]" << std::endl;


		//Get memory free
		unsigned int memory_free = GetDeviceMemoryFree(0);
		std::cout << memory_free << std::endl;


		//Get memory used
		unsigned int memory_used = GetDeviceMemoryUsed(0);
		std::cout << memory_used << std::endl;


		//Get memory total
		unsigned int memory_total = GetDeviceMemoryTotal(0);
		std::cout << memory_total << std::endl;

		std::cout << std::endl;

		Sleep(5000);
	}
	

	//nvmlDevice_t device;

	//nvmlReturn_t result;

	//nvmlDeviceGetHandleByIndex(gpu_id, &device);

	//result = nvmlInit();
	//if (NVML_SUCCESS != result)
	//{
	//	std::cout << "Failed to initialize NVML: " << nvmlErrorString(result) << std::endl;
	//}

	////Attached GPU count
	//unsigned int device_count;
	//result = nvmlDeviceGetCount(&device_count);
	//if (NVML_SUCCESS != result)
	//{
	//	std::cout << "Failed to query get device count: " << nvmlErrorString(result) << std::endl;
	//}
	//else
	//{
	//	std::cout << "Attached: " << device_count << std::endl;
	//}

	//


	////GPU name
	//char device_name[64];
	//result = nvmlDeviceGetName(device, device_name, 64);
	//if (NVML_SUCCESS != result)
	//{
	//	std::cout << "Failed to query get device name: " << nvmlErrorString(result) << std::endl;
	//}
	//else
	//{
	//	std::cout << "Name: " << device_name << std::endl;
	//}


	////NVML version
	//char nvml_ver[64];
	//result = nvmlSystemGetNVMLVersion(nvml_ver, 64);
	//if (NVML_SUCCESS != result)
	//{
	//	std::cout << "Failed to query get NVML version: " << nvmlErrorString(result) << std::endl;
	//}
	//else
	//{
	//	std::cout << "NVML version: " << nvml_ver << std::endl;
	//}



	////Driver version
	//char driver_ver[64];
	//result = nvmlSystemGetDriverVersion(driver_ver, 64);
	//if (NVML_SUCCESS != result)
	//{
	//	std::cout << "Failed to query get driver version: " << nvmlErrorString(result) << std::endl;
	//}
	//else
	//{
	//	std::cout << "Driver version: " << driver_ver << std::endl;
	//}
	//


	////CUDA version
	//int cuda_ver;
	//result = nvmlSystemGetCudaDriverVersion(&cuda_ver);
	//if (NVML_SUCCESS != result)
	//{
	//	std::cout << "Failed to query get CUDA version: " << nvmlErrorString(result) << std::endl;
	//}
	//else
	//{
	//	std::cout << "CUDA version: " << NVML_CUDA_DRIVER_VERSION_MAJOR(cuda_ver) << "." << NVML_CUDA_DRIVER_VERSION_MINOR(cuda_ver) << std::endl;
	//}


	//std::cout << std::endl;

	//std::cout << "test : monitor GPU Info" << std::endl;
	////monitor temp
	//while (true)
	//{

	//	//show timestamp
	//	std::cout << GetTimeStamp() << std::endl;


	//	//bug!!!
	//	//Power util
	//	unsigned int power;
	//	result = nvmlDeviceGetPowerUsage(device, &power);
	//	if (NVML_SUCCESS != result)
	//	{
	//		std::cout << "Failed to query get power util: " << nvmlErrorString(result) << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "Power util: " << power / 1000.0 << "[W]" << std::endl;
	//	}



	//	//Temperature
	//	unsigned int temp;
	//	result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
	//	if (NVML_SUCCESS != result)
	//	{
	//		std::cout << "Failed to query get temperature: " << nvmlErrorString(result) << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "Temp: " << temp << "[C]" << std::endl;
	//	}



	//	//Fan speed
	//	unsigned int device_fanspeed;
	//	result = nvmlDeviceGetFanSpeed(device, &device_fanspeed);
	//	if (NVML_SUCCESS != result)
	//	{
	//		std::cout << "Failed to query get fan speed: " << nvmlErrorString(result) << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << device_fanspeed << std::endl;
	//	}



	//	//GPU util
	//	nvmlUtilization_t device_util;
	//	result = nvmlDeviceGetUtilizationRates(device, &device_util);
	//	if (NVML_SUCCESS != result)
	//	{
	//		std::cout << "Failed to query get GPU usage: " << nvmlErrorString(result) << std::endl;
	//	}
	//	else
	//	{

	//		std::cout << "GPU: " << device_util.gpu << "[%]" << std::endl;
	//		std::cout << "Memory: " << device_util.memory << "[%]" << std::endl;
	//	}

	//	//Memory info
	//	nvmlMemory_t memory;
	//	result = nvmlDeviceGetMemoryInfo(device, &memory);
	//	if (NVML_SUCCESS != result)
	//	{
	//		std::cout << "Failed to query get memory info: " << nvmlErrorString(result) << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << "Memory info" << std::endl;
	//		std::cout << "Free: " << memory.free / 1000000 << "[MB]" << std::endl;
	//		std::cout << "Used: " << memory.used / 1000000 << "[MB]" << std::endl;
	//		std::cout << "Total: " << memory.total / 1000000 << "[MB]" << std::endl;
	//	}


	//	std::cout << std::endl;

	//	Sleep(5000);
	//}



	nvmlShutdown();



}