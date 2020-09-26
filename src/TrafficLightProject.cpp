#include<iostream>
#include<cstdlib>
#include<numeric>
#include<string>
//#include"TrafficSignal.h"
//#include"Publisher.h"
#include"SignalController.h"

int main(int c, char* argv[])
{
	std::cout<<"Hello World"<<std::endl;

	SignalController *publisher = new SignalController();
	TrafficSignal trafficSignal1, trafficSignal2;
	publisher->attach(&trafficSignal1);
	publisher->attach(&trafficSignal2);

	publisher->startComputing();
	
	return 0;
}

