#include "SignalController.h"
#include<chrono>
#include<thread>

SignalController::SignalController(){

}

SignalController::~SignalController(){


}

std::string SignalController::stateToString(TrafficLight tempLight)
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

void SignalController::startComputing()
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
		this->notify(0, true);
		
		auto end = std::chrono::steady_clock::now();
		auto elapsed = end - start;

		auto timeToWait = timeWindow - elapsed;
		if(timeToWait > std::chrono::milliseconds::zero())
		{
			std::this_thread::sleep_for(timeToWait);
		}
	}

}

void SignalController::startComputing(uint totalPer, uint amberPer, uint commonRedPer)
{
    const auto timeWindow = std::chrono::milliseconds(1000);
	uint totalPeriod = totalPer;
	uint amberPeriod = amberPer;
	uint commonRedPeriod = commonRedPer;
    uint counter = 0;

    //Some calculations for states
    std::cout<<"Here1"<<std::endl;
    uint greenRedPeriod = (totalPeriod - (2*amberPeriod) - commonRedPeriod)/2;
    std::cout<<"greenRedPeriod = "<<greenRedPeriod<<std::endl;

    bool firstUse = true;

    while(true)
	{
		auto start = std::chrono::steady_clock::now();
        if(firstUse) 
        { 
            currentState = none;
            //previousState = none;
            movingStateMachine(); 
            firstUse = false;

            //currentState = StateGreenRed;
            //movingStateMachine();
        }
        else
        {
            if(counter == greenRedPeriod || counter == (greenRedPeriod+amberPeriod) 
                || counter == (greenRedPeriod+commonRedPeriod) || counter == (greenRedPeriod + commonRedPeriod + (2*amberPeriod)))
            {
                movingStateMachine();

            }
        }

        if(counter == greenRedPeriod + (2*amberPeriod) + commonRedPeriod) { counter = 0; }
        else { counter++; }

        auto end = std::chrono::steady_clock::now();
		auto elapsed = end - start;

		auto timeToWait = timeWindow - elapsed;
		if(timeToWait > std::chrono::milliseconds::zero())
		{
			std::this_thread::sleep_for(timeToWait);
		}             
    }

}

void SignalController::movingStateMachine()
{
    switch(currentState) {
        case none:
            //first case
            notify(StateRedRed, true);
            notify(StateGreenRed, true);
            break;
        case StateGreenRed:
            previousState = StateGreenRed;
            currentState = StateAmberRed;
            notify(currentState, true);
            break;
        case StateAmberRed:
            if(previousState == StateRedRed)
            {
                currentState = StateGreenRed;
            }
            else
            {
                currentState = StateRedRed;
            }      
            previousState = StateAmberRed;
            notify(currentState, true);
            break;
        case StateRedRed:
            if(previousState == StateRedAmber)
            {
                currentState = StateAmberRed;
            }
            else
            {
                currentState = StateRedAmber;
            }
            previousState = StateRedRed;
            notify(currentState, true);
            break;
        case StateRedAmber:
            if(previousState == StateRedRed)
            {
                currentState = StateRedGreen;
            }
            else
            {
                currentState = StateRedRed;
            } 
            previousState = StateRedAmber;
            notify(currentState, true);
            break;
        case StateRedGreen:
            previousState = StateRedGreen;
            currentState = StateRedAmber;
            notify(currentState, true);
            break;
        default:
            break;
    }
}
