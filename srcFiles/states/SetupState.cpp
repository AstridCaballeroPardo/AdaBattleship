#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/SetupState.h"
#include "../../headerFiles/Grid.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"


    //Constructor
    SetupState::SetupState():BaseState(){}
    //Destructor
    SetupState::~SetupState(){}

    //member methods
    void SetupState::enter()
    {
      
      manuallySetFleet(StateMachine::getInstance()->getGridPlayer1());  
      
      StateMachine::getInstance()->getGridPlayer2()->renderGrid();
      automaticallySetFleet(StateMachine::getInstance()->getGridPlayer2());  
      
      render();
    }
    void SetupState::exit(){}
    void SetupState::update()
    {
      //transition to next state
      StateMachine::getInstance()->change("play"); 
    }
    void SetupState::render()
    {
      StateMachine::getInstance()->getGridPlayer1()->renderGrid();
      StateMachine::getInstance()->getGridPlayer2()->renderGrid();
      //move to the play state
      update();
    }