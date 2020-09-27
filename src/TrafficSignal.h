#include "Observer.h"

//state machine. Can move it to util 
enum AdvStat{
    StateGR = 1,
    StateAR,
    StateRR,
    StateRA,
    StateRG,
    NN
};

/**
 * @brief Derived class of Observer. Listens to signals from publisher
 * and prints the color to the screen.
 * 
 */
class TrafficSignal : public Observer {
public:

    uint identifier;
    TrafficSignal(uint signalIdentifier);
    ~TrafficSignal();
    void update(uint value, bool publishOnScreen);
};