#pragma once

#include "../StateMachine.h"
#include "BaseState.h"
#include "../Grid.h"

class SetupState: public BaseState {
  private:
    Grid gridPlayer;
    Grid gridComputer;
    
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