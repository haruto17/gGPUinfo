#include<iostream>
#include<windows.h>
#include"nvml/nvml.h"

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
		std::cout << "Attached: " << device_count << std::endl;
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



	//Power util
	unsigned int power;
	result = nvmlDeviceGetPowerUsage(device, &power);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get power util: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << "Power util: " << power / 1000.0 << "[W]" << std::endl;
	}



	//Temperature
	unsigned int temp;
	result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get temperature: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << "Temp: " << temp << "[C]" << std::endl;
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


	//GPU util
	nvmlUtilization_t device_util;
	result = nvmlDeviceGetUtilizationRates(device, &device_util);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get GPU usage: " << nvmlErrorString(result) << std::endl;
	}
	else
	{

		std::cout << "GPU: " << device_util.gpu << "[%]" << std::endl;
		std::cout << "Memory: " << device_util.memory << "[%]" << std::endl;
	}


	//Memory info
	nvmlMemory_t memory;
	result = nvmlDeviceGetMemoryInfo(device, &memory);
	if (NVML_SUCCESS != result)
	{
		std::cout << "Failed to query get memory info: " << nvmlErrorString(result) << std::endl;
	}
	else
	{
		std::cout << "Memory info" << std::endl;
		std::cout << "Free: " << memory.free << "[B]" << std::endl;
		std::cout << "Used: " << memory.used << "[B]" << std::endl;
		std::cout << "Total: " << memory.total << "[B]" << std::endl;
	}
	

	std::cout << std::endl;

	std::cout << "test : monitor GPU temp" << std::endl;
	//monitor temp
	while (true)
	{
		//Temperature
		unsigned int temp;
		result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
		if (NVML_SUCCESS != result)
		{
			std::cout << "Failed to query get temperature: " << nvmlErrorString(result) << std::endl;
		}
		else
		{
			std::cout << "Temp: " << temp << "[C]" << std::endl;
		}

		Sleep(3000);
	}



	//nvmlShutdown();



}