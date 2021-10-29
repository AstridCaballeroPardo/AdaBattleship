#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/SetupState.h"
#include "../../headerFiles/Grid.h"
#include "../../headerFiles/Fleet.h"
#include "../../headerFiles/Tile.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"

#include <unistd.h>


//Constructor
SetupState::SetupState():BaseState(){}
//Destructor
SetupState::~SetupState(){}

//member methods
void SetupState::enter()
{
  //ask type of game to play
  std::string input;
  std::string msg;
  
  msg = "Select from the menu: \n1. One player vs computer game\n2. Two player game\n3. Quit\n";

  input = userInput(msg);

  if (input == "1") 
  {
    StateMachine::getInstance()->getGridPlayer1()->setPlayerType("human"); 
    StateMachine::getInstance()->getGridPlayer2()->setPlayerType("computer");

    while(true) {
      std::cout << YELLOW << "PlayerA set your fleet: \n" << ENDCOLOUR;
      manuallySetFleet(StateMachine::getInstance()->getGridPlayer1());
      
      std::string inputMenuReset = menuContinue();
      //reset
      if (inputMenuReset == "2")
      { 
        StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
      }
      else if(inputMenuReset == "3")
      {
        exit();
      }
      else 
      {
        break;
      }
    }
      
    std::cout << GREEN << "\nComputer placing Fleet...\n\n" << ENDCOLOUR;
    //add a time delay to improve game's pace.
    usleep(2000000);
    automaticallySetFleet(StateMachine::getInstance()->getGridPlayer2());
        
    
  }  
  else if(input == "2") 
  {
    StateMachine::getInstance()->getGridPlayer1()->setPlayerType("human"); 
    StateMachine::getInstance()->getGridPlayer2()->setPlayerType("human");

      while(true) {
      std::cout << YELLOW << "PlayerA set your fleet: \n" << ENDCOLOUR;
      manuallySetFleet(StateMachine::getInstance()->getGridPlayer1());

      std::string inputMenuReset = menuContinue();
      //reset
      if (inputMenuReset == "2")
      {    
      StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
      }
      else if(inputMenuReset == "3")
      {
        exit();
      }
      else 
      {
        break;
      }
    }

      while(true) {
      std::cout << YELLOW << "PlayerB set your fleet: \n" << ENDCOLOUR;
      manuallySetFleet(StateMachine::getInstance()->getGridPlayer2());

      std::string inputMenuReset = menuContinue();
      //reset
      if (inputMenuReset == "2")
      {    
      StateMachine::getInstance()->getGridPlayer2()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer2()->getGrid());
      }
      else if(inputMenuReset == "3")
      {
        exit();
      }
      else 
      {
        break;
      }
    }       
  }
  else
  {
    exit();
  }
  
  render();
}

void SetupState::exit()
{
  //transition back to intro
  StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
  
  StateMachine::getInstance()->getGridPlayer2()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer2()->getGrid());
  StateMachine::getInstance()->change("intro"); 
}
void SetupState::update()
{
  //transition to next state
  StateMachine::getInstance()->change("play"); 
}
void SetupState::render()
{

  std::cout << YELLOW << "PlayerA Fleet\n" << ENDCOLOUR;
  StateMachine::getInstance()->getGridPlayer1()->renderGrid();

  std::cout << "\n\n";

  if (StateMachine::getInstance()->getGridPlayer2()->getPlayerType() == "computer")
  {
  std::cout << YELLOW << "Computer Fleet\n" << ENDCOLOUR;
  StateMachine::getInstance()->getGridPlayer2()->renderGrid();
  }
  else if (StateMachine::getInstance()->getGridPlayer2()->getPlayerType() == "human")
  {
  std::cout << YELLOW << "PlayerB Fleet\n" << ENDCOLOUR;
  StateMachine::getInstance()->getGridPlayer2()->renderGrid();
  }

  std::string inputMenuToPlay = menuTransToPlay();
  if (inputMenuToPlay == "1") {
    //move to the play state
    update();
  }
  else
  {
    exit();
  }
  
}