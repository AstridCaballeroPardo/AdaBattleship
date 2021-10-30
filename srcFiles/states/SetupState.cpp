#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/SetupState.h"
#include "../../headerFiles/Grid.h"
#include "../../headerFiles/Fleet.h"
#include "../../headerFiles/Tile.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"

#include <unistd.h>

bool continueResetQuit(Grid* grid) {
  std::string input;
  input = menuContinue();
  if (input == "1") 
  {
    return true;
  }
  else if (input == "2") 
  {
    StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
    return true;
  }
  else 
  {
    return false;
  }
}


void placing(Grid* grid) 
{
  std::string input;
  input = menuSetFleet();
  if (input == "1") 
  {
    manuallySetFleet(grid);
  }
  else if (input == "2") 
  {
    automaticallySetFleet(grid);     
  }
}

//more refactoring
void playerTurn(Grid* grid) 
{
  //keep placing for player or quit?
  grid->renderGrid();
  placing(grid);
  grid->renderGrid();
}



//refactoring
void setPlayersType(Grid* gridPlayer1, Grid* gridPlayer2, std::string type) {
  if (type == "1") {
    gridPlayer1->setPlayerType("human"); 
    gridPlayer2->setPlayerType("computer");
  }
  else if (type == "2") {
    gridPlayer1->setPlayerType("human"); 
    gridPlayer2->setPlayerType("human");
  }
}




//Constructor
SetupState::SetupState():BaseState(){}
//Destructor
SetupState::~SetupState(){}

//member methods
void SetupState::enter()
{
  bool isNotQuit = true;
  
  //ask type of game to play
  std::string input;

  input = menuGameType();
  
  //set type of players human/computer
  setPlayersType(StateMachine::getInstance()->getGridPlayer1(), StateMachine::getInstance()->getGridPlayer2(), input);
  
  //player vs computer
  if (input == "1") 
  {
    while(!isFleetCompleted(StateMachine::getInstance()->getGridPlayer1())) {
           
      std::cout << YELLOW << "\nPlayerA set your fleet: \n" << ENDCOLOUR;
      
      playerTurn(StateMachine::getInstance()->getGridPlayer1()); 
           
      isNotQuit = continueResetQuit(StateMachine::getInstance()->getGridPlayer1());
      if(!isNotQuit) {
        break;
      }
    }
    
    if (!isNotQuit) 
    {
      exit();
    }  
    //next player
    else 
    {
      std::cout << GREEN << "\nComputer placing Fleet...\n\n" << ENDCOLOUR;
      //add a time delay to improve game's pace.
      usleep(2000000);
      automaticallySetFleet(StateMachine::getInstance()->getGridPlayer2());  
      render ();
    }  
  }  
  else if(input == "2") 
  {
    while(!isFleetCompleted(StateMachine::getInstance()->getGridPlayer1())) {
           
      std::cout << YELLOW << "\nPlayerA set your fleet: \n" << ENDCOLOUR;
      
      playerTurn(StateMachine::getInstance()->getGridPlayer1()); 
           
      isNotQuit = continueResetQuit(StateMachine::getInstance()->getGridPlayer1());
      if(!isNotQuit) {
        break;
      }
    }
    
    if (!isNotQuit) 
    {
      exit();
    }  
    //next player
    else 
    {
       while(!isFleetCompleted(StateMachine::getInstance()->getGridPlayer2())) {
           
        std::cout << YELLOW << "\nPlayerB set your fleet: \n" << ENDCOLOUR;
        
        playerTurn(StateMachine::getInstance()->getGridPlayer2()); 
            
        isNotQuit = continueResetQuit(StateMachine::getInstance()->getGridPlayer2());
        if(!isNotQuit) {
          break;
        }
      }
      if (!isNotQuit) 
      {
        exit();
      }
      else 
      {
        render ();
      } 
    }   
  }
}

void SetupState::exit()
{
  // transition back to intro
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
  else {
    exit();
  }
}