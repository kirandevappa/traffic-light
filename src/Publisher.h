//#include<iostream>
#include<vector>
#include<algorithm>
#include "TrafficSignal.h"

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