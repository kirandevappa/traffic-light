#include "Publisher.h"

//constructor
Publisher::Publisher()
{

}

//Destructor
Publisher::~Publisher()
{

}

void Publisher::attach(TrafficSignal *obs)
{
    listeners.push_back(obs);
}

void Publisher::detach(TrafficSignal *obs)
{
    listeners.erase(std::remove(listeners.begin(), listeners.end(), obs), listeners.end());
}

void Publisher::notify(uint value, bool publishOnScreen)
{
    for(unsigned int i = 0; i<(unsigned int)listeners.size(); ++i)
    {
        listeners[i]->update( value, publishOnScreen);
    }
    std::cout<<std::endl;
}

