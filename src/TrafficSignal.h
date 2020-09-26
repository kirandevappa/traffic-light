#include "Observer.h"

class TrafficSignal : public Observer {
public:
    TrafficSignal();
    ~TrafficSignal();
    void update();
};