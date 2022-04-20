#include<iostream>

int main()
{
	//Get GPU name
	system("nvidia-smi --list-gpus");

	//Get GPU temperature
	system("nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader");

	return 0;
}