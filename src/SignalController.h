#include "Publisher.h"
//#include "util.h"


enum AdvancedStates{
    StateGreenRed = 1,
    StateAmberRed,
    StateRedRed,
    StateRedAmber,
    StateRedGreen,
    none
};

class SignalController : public Publisher{
public:
    SignalController();
    ~SignalController();

   // void startComputing();
    void startComputing(uint totalPer, uint amberPer, uint commonRedPer);
    void movingStateMachine();

    AdvancedStates currentState;
    AdvancedStates previousState;

};