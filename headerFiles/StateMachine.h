#pragma once

#include "states/BaseState.h"
#include <iostream>
#include <map>


//StateMachine class Points at something that is active (active state)
class StateMachine {
  private:
    std::map<std::string, BaseState*> states_;
    BaseState currentState = nullptr;
    
  public:
    //Constructor
    StateMachine(std::map<std::string, BaseState*> states);
    //Destructor
    ~StateMachine();
    
    //StateMachine member methods
    void change(BaseState* state);
    void update();
    void render();
};