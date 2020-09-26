#include "Observer.h"

enum AdvStat{
    StateGR = 1,
    StateAR,
    StateRR,
    StateRA,
    StateRG,
    NN
};


class TrafficSignal : public Observer {
public:
   // SignalController *signalController;
    uint identifier;
    TrafficSignal(uint signalIdentifier);
    ~TrafficSignal();
    void update(uint value, bool publishOnScreen);
};