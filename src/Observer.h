#include<iostream>

class Observer {
public:
    virtual void update(uint value, bool publishOnScreen) = 0;
};
