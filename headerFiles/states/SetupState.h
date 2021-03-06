#pragma once

#include "BaseState.h"
#include "../StateMachine.h"

class SetupState: public BaseState {
  public:
    //Constructor
    SetupState();
    //Destructor
    ~SetupState();

    //member methods
    void enter();
    void exit();
    void update();
    void render();
};