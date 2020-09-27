#include<iostream>
#include<cstdlib>
#include<numeric>
#include<string>
#include"SignalController.h"

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> SOURCES" <<std::endl
              << "Options:\n" <<std::endl
			  << " -f,--fullcycle\t\tGreen to Green cycle time in seconds"<<std::endl
			  << " -a,--amber\t\tAmber time in seconds before red"<<std::endl
			  << " -r,--redfull\t\tRed time in seconds for all signals"<<std::endl
              << "-h,--help\t\tShow this help message"<<std::endl
              << "-d,--default \t\t -f 40 -a 2 -r 2"<<std::endl
              << std::endl;
}

int main(int argc, char* argv[])
{
	uint fullCycle = 40;
	uint amberTime = 2;
	uint redTime = 2;

	//Parameterize

	SignalController *publisher = new SignalController();

	for(uint i=1; i<=4; i++)
	{
		publisher->attach(new TrafficSignal(i));
	}

	publisher->startComputing(fullCycle, amberTime, redTime);

	return 0;
}

