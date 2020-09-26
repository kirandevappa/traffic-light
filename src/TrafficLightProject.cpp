#include<iostream>
#include<cstdlib>
#include<chrono>
#include<numeric>
#include<thread>
#include<string>
//#include"TrafficSignal.h"
#include"Publisher.h"

enum StateMachine{
	stateGreen = 1,
	stateAmber,
	stateWaitingGreen,
	stateRed
};

struct TrafficLight{
	unsigned int reverseCounter = 0;
	enum StateMachine currentState = stateRed;
};

std::string stateToString(TrafficLight tempLight)
{
	std::string returnStr;
	if(tempLight.currentState == stateWaitingGreen || tempLight.currentState == stateRed)
	{
		returnStr = "RED"; 
	}
	else if(tempLight.currentState == stateAmber)
	{
		returnStr = "AMBER";
	}
	else
	{
		returnStr = "GREEN";
	}
	return returnStr;
}

void startComputing(Publisher *publisher)
{
	const auto timeWindow = std::chrono::milliseconds(1000);
	unsigned int totalPeriod = 40;
	unsigned int amberPeriod = 2;
	unsigned int commonRedPeriod = 2;
	bool firstUse = true;

	TrafficLight lightsEven, lightsOdd;
	std::string lightsEvenString, lightsOddString;
	lightsEvenString = "RED";
	lightsOddString = "RED";


	while(true)
	{
		auto start = std::chrono::steady_clock::now();
		
		//std::cout<<"Inside Here"<<std::endl;
		
		//trafficAlgorithm();

		//first use
		if(firstUse == true)
		{
			lightsEven.reverseCounter = 16;
			lightsOdd.reverseCounter = totalPeriod - (amberPeriod + commonRedPeriod);
			firstUse = false;

		}

		if(lightsEven.reverseCounter == totalPeriod - (amberPeriod + commonRedPeriod))
		{
			lightsOdd.currentState = stateAmber;
		}
		else if(lightsOdd.reverseCounter == totalPeriod - (amberPeriod + commonRedPeriod))
		{
			lightsEven.currentState = stateAmber;
		}
		else if(lightsEven.reverseCounter == totalPeriod - commonRedPeriod)
		{
			lightsOdd.currentState = stateWaitingGreen;
		}
		else if(lightsOdd.reverseCounter == totalPeriod - commonRedPeriod)
		{
			lightsEven.currentState = stateWaitingGreen;
		}
		else if(lightsEven.reverseCounter == totalPeriod)
		{
			lightsEven.currentState = stateGreen;
		}
		else if(lightsOdd.reverseCounter == totalPeriod)
		{
			lightsOdd.currentState = stateGreen;
		}
		else
		{
			//std::cout<<"Unexpected Transition"<<std::endl;
		}

		if(lightsEven.reverseCounter == totalPeriod)
		{
			lightsEven.reverseCounter = 0;
		}
		else
		{
			lightsEven.reverseCounter++;
		}

		if(lightsOdd.reverseCounter == totalPeriod)
		{
			lightsOdd.reverseCounter = 0;
		}
		else
		{
			lightsOdd.reverseCounter++;
		}

		std::cout<<"Light Even :" << stateToString(lightsEven)<<" Light Odd :" << stateToString(lightsOdd) <<std::endl;
		publisher->notify();
		
		auto end = std::chrono::steady_clock::now();
		auto elapsed = end - start;

		auto timeToWait = timeWindow - elapsed;
		if(timeToWait > std::chrono::milliseconds::zero())
		{
			std::this_thread::sleep_for(timeToWait);
		}
	}
}

int main(int c, char* argv[])
{
	std::cout<<"Hello World"<<std::endl;

	Publisher *publisher = new Publisher();
	TrafficSignal trafficSignal1, trafficSignal2;
	publisher->attach(&trafficSignal1);
	publisher->attach(&trafficSignal2);


	startComputing(publisher);
	return 0;
}

