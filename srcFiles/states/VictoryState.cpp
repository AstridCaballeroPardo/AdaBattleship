#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/VictoryState.h"
#include "../../headerFiles/constants.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"

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
      
      render();
    };
    void VictoryState::exit(){}
    void VictoryState::update()
    {
      //transition to intro state
      StateMachine::getInstance()->change("intro"); 
    }

    void VictoryState::render()
    {
      std::cout << YELLOW << "you win!!! Campe@n! :)\n\n" << ENDCOLOUR;      
      std::string input = menuEndGame();
      if (input.length() == 1) {
        //move to intro state
        update();
      }      
    }