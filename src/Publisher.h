//#include<iostream>
#include<vector>
#include<algorithm>
#include "TrafficSignal.h"

/**
 * @brief Publisher base class. A class responsible to publish and notify to listeners
 * 
 */

class Publisher{
private:
    std::vector<class TrafficSignal *> listeners;
    int value;

public:
    Publisher();
    ~Publisher();
    void attach(TrafficSignal *obs);
    void detach(TrafficSignal *obs);
    void notify(uint value, bool publishOnScreen);
};