#include "TrafficSignal.h"

TrafficSignal::TrafficSignal(uint signalIdentifier)
{
    identifier = signalIdentifier;
}

TrafficSignal::~TrafficSignal(){

}

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