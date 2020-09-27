#include "TrafficSignal.h"

/**
 * @brief Construct a new Traffic Signal:: Traffic Signal object
 * 
 * @param signalIdentifier 
 */
TrafficSignal::TrafficSignal(uint signalIdentifier)
{
    identifier = signalIdentifier;
}

/**
 * @brief Destroy the Traffic Signal:: Traffic Signal object
 * 
 */
TrafficSignal::~TrafficSignal(){

}

/**
 * @brief Function called during an update notification from publisher
 * Responsible to turn the signal to appropriate light color
 * 
 * @param value 
 * @param publishOnScreen 
 */
void TrafficSignal::update(uint value, bool publishOnScreen)
{
    //do nothing for now
    std::string color = "";
    if(identifier%2 != 0)
    { 
        switch(value) {
            case StateGR:
                color = "GREEN";
                break;
            case StateAR:
                color = "AMBER";
                break;
            default:
                color = "RED";
                break;

        }
    }
    else
    {
        switch(value) {
            case StateRA:
                color = "AMBER";
                break;
            case StateRG:
                color = "GREEN";
                break;
            default:
                color = "RED";
                break;
        }
    }
    if(publishOnScreen){ std::cout<<"Signal "<<identifier<<"="<<color<<" "; }
}