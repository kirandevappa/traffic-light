#include<iostream>
/**
 * @brief Base class Observer to observe for events
 * 
 */
class Observer {
public:
    virtual void update(uint value, bool publishOnScreen) = 0;
};
