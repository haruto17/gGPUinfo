#include<iostream>
#include<string>
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
	
	std::cout << std::endl;

	std::cout << "test : monitor GPU Info" << std::endl;
	//monitor temp
	while (true)
	{

		//show timestamp
		std::cout << GetTimeStamp() << std::endl;


		//bug!!!
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

		Sleep(5000);
	}



	nvmlShutdown();



}