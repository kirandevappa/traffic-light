#include "Publisher.h"

enum StateMachine{
	stateGreen = 1,
	stateAmber,
	stateWaitingGreen,
	stateRed
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

};