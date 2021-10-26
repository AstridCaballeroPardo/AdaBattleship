#pragma once

#include "BaseState.h"
#include "../StateMachine.h"

#include <map>
#include <string>
#include <memory>

class IntroState:public BaseState {
  public:
    //Constructor
    IntroState();
    //Destructor
    ~IntroState();

    //member methods
    void enter();
    void exit();
    void update();
    void render();
};