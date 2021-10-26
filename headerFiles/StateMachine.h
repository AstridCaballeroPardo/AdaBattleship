#pragma once

#include "states/BaseState.h"
#include <iostream>
#include <map>


//StateMachine class Points at something that is active (active state). Using this class to implement the State Pattern
class StateMachine {
  //StateMachine class is created using the Singleton pattern
  private:
    //Constructor
    StateMachine();
    static StateMachine* inst_; 
  
  protected:
    std::map<std::string, BaseState*> states_;
    BaseState* currentState = nullptr;
    
  public:
    StateMachine(StateMachine &other) = delete; 
    void operator = (const StateMachine &) = delete; 
    
    //Destructor
    ~StateMachine();

    static StateMachine *getInstance();
    
    //StateMachine member methods
    void change(std::string state);
    void update();
    void render();
    
};