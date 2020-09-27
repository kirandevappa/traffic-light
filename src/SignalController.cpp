#include "SignalController.h"
#include<chrono>
#include<thread>

SignalController::SignalController(){
}

SignalController::~SignalController(){
}

void SignalController::startComputing(uint totalPer, uint amberPer, uint commonRedPer)
{
    const auto timeWindow = std::chrono::milliseconds(1000);
	uint totalPeriod = totalPer;
	uint amberPeriod = amberPer;
	uint commonRedPeriod = commonRedPer;
    uint counter = 0;

    //Some calculations for states
    uint greenRedPeriod = (totalPeriod - (2*amberPeriod) - (2*commonRedPeriod))/2;

    bool firstUse = true;

    while(true)
	{
		auto start = std::chrono::steady_clock::now();
        if(firstUse) 
        { 
            currentState = none;
            movingStateMachine(); 
            firstUse = false;
        }
        else
        {
            if(counter == greenRedPeriod || counter == (greenRedPeriod+amberPeriod) 
                || counter == (greenRedPeriod+amberPeriod+commonRedPeriod))
            {
                movingStateMachine();
            }
        }

        if(counter == greenRedPeriod + (amberPeriod) + commonRedPeriod) { counter = 0; }
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
            currentState = StateGreenRed;
            break;
        case StateGreenRed:
            previousState = StateGreenRed;
            currentState = StateAmberRed;
            notify(currentState, true);
            break;
        case StateAmberRed:   
            previousState = StateAmberRed;
            currentState = StateRedRed;
            notify(currentState, true);
            break;
        case StateRedRed:
            if(previousState == StateRedAmber)
            {
                currentState = StateGreenRed;
            }
            else 
            {
                currentState = StateRedGreen;
            }
            previousState = StateRedRed;
            notify(currentState, true);
            break;
        case StateRedAmber:
            previousState = StateRedAmber;
            currentState = StateRedRed;
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
