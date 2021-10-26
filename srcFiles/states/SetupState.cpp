#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/SetupState.h"
#include "../../headerFiles/Grid.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"


    //Constructor
    SetupState::SetupState():BaseState()
    {
      Grid gridPlayer;
      Grid gridComputer; 
    }
    //Destructor
    SetupState::~SetupState(){}

    //member methods
    void SetupState::enter()
    {
      // Grid gridPlayer;
      manuallySetFleet(gridPlayer);  
      // gridPlayer.renderGrid();

      // Grid gridComputer; 
      gridComputer.renderGrid();
      automaticallySetFleet(gridComputer);  
      // gridComputer.renderGrid();
      render();
    }
    void SetupState::exit(){}
    void SetupState::update()
    {
      
    }
    void SetupState::render()
    {
      gridPlayer.renderGrid();
      gridComputer.renderGrid();
    }