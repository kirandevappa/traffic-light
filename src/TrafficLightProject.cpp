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
	TrafficSignal trafficSignal1(1), trafficSignal2(2), trafficSignal3(3), trafficSignal4(4);
	publisher->attach(&trafficSignal1);
	publisher->attach(&trafficSignal2);
	publisher->attach(&trafficSignal3);
	publisher->attach(&trafficSignal4);

	publisher->startComputing(40, 2, 2);

	return 0;
}

