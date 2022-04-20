#include<iostream>

int main()
{
	//Get timestamp
	system("nvidia-smi --query-gpu=timestamp --format=csv");

	std::cout << std::endl;

	//Get GPU name
	system("nvidia-smi --query-gpu=gpu_name --format=csv");

	std::cout << std::endl;

	//Get driver_version
	system("nvidia-smi --query-gpu=driver_version --format=csv");

	std::cout << std::endl;

	//Get GPU temperature
	system("nvidia-smi --query-gpu=temperature.gpu --format=csv");

	std::cout << std::endl;

	//Get GPU utilization
	system("nvidia-smi --query-gpu=utilization.gpu --format=csv");

	std::cout << std::endl;

	//Get GPU memory utilization
	system("nvidia-smi --query-gpu=utilization.memory --format=csv");

	std::cout << std::endl;

	//Get total GPU memory
	system("nvidia-smi --query-gpu=memory.total --format=csv");

	std::cout << std::endl;

	//Get free GPU memory
	system("nvidia-smi --query-gpu=memory.free --format=csv");

	std::cout << std::endl;

	//Get used GPU memory
	system("nvidia-smi --query-gpu=memory.used --format=csv");

	return 0;
}