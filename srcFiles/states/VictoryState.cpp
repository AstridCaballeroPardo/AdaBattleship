#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/VictoryState.h"
#include "../../headerFiles/constants.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"

#include <string>
#include <iostream>

    //Constructor
    VictoryState::VictoryState():BaseState() {}
    //Destructor
    VictoryState::~VictoryState(){};

    //member methods
    void VictoryState::enter(int params)
    {      
      if (params == 1) {
        std::cout << YELLOW << "\nPlayerA " << ENDCOLOUR;  
      }
      else {
        std::cout << YELLOW << "\nPlayerB " << ENDCOLOUR;
      }    
      exit();
    }

    void VictoryState::exit()
    {
      //clean
      Grid& grid1 = *StateMachine::getInstance()->getGridPlayer1();
      Grid& grid2 = *StateMachine::getInstance()->getGridPlayer2();      

      std::vector<int>& bombedTilesGrid1 = StateMachine::getInstance()->getBombedTilesGrid1();
      std::vector<int>& bombedTilesGrid2 = StateMachine::getInstance()->getBombedTilesGrid1();

      //reset ships
      grid1.getFleet().resetFleet(grid1.getGrid());
      //reset bombed empty tiles 
      resetBombedTiles(grid1, bombedTilesGrid1);
      
      //reset ships
      grid2.getFleet().resetFleet(grid2.getGrid());
      //reset bombed empty tiles 
      resetBombedTiles(grid2, bombedTilesGrid2);
      render();
    }
    void VictoryState::update()
    {
      //transition to intro state
      StateMachine::getInstance()->change("intro"); 
    }

    void VictoryState::render()
    {
      std::cout << YELLOW << "you win!!! Campe@n! :)\n\n" << ENDCOLOUR;      
      std::string input = menuEndGame();
      if (input == "1") {
        //move to intro state
        update();
      }      
    }