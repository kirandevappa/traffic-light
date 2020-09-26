#include "Publisher.h"
//#include "util.h"

enum StateMachine{
	stateGreen = 1,
	stateAmber,
	stateWaitingGreen,
	stateRed
};

enum AdvancedStates{
    StateGreenRed = 1,
    StateAmberRed,
    StateRedRed,
    StateRedAmber,
    StateRedGreen,
    none
};

struct TrafficLight{
	unsigned int reverseCounter = 0;
	enum StateMachine currentState = stateRed;
};


class SignalController : public Publisher{
public:
    SignalController();
    ~SignalController();

    std::string stateToString(TrafficLight tempLight);
    void startComputing();
    void startComputing(uint totalPer, uint amberPer, uint commonRedPer);
    void movingStateMachine();

    AdvancedStates currentState;
    AdvancedStates previousState;

};