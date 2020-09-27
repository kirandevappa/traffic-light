#include "Publisher.h"
//#include "util.h"

/**
 * @brief 
 * 
 */
enum AdvancedStates{
    StateGreenRed = 1,
    StateAmberRed,
    StateRedRed,
    StateRedAmber,
    StateRedGreen,
    none
};

/**
 * @brief Class Signal controller, extends Base Publisher. 
 * Responsible for core scheduling algorithm and publishing to listener signals
 * 
 */
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