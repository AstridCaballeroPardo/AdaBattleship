#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/SetupState.h"
#include "../../headerFiles/Grid.h"
#include "../../headerFiles/Fleet.h"
#include "../../headerFiles/Tile.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"

#include <unistd.h>

bool playAfterFleetset(Grid* grid) {
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



bool howToPLaceFleet(Grid* grid) 
{
  std::string input;
  input = menuSetFleet();
  if (input == "1") 
  {
    manuallySetFleet(StateMachine::getInstance()->getGridPlayer1()); 
    return true;
  }
  else if (input == "2") 
  {
    automaticallySetFleet(StateMachine::getInstance()->getGridPlayer1());

    //are happy with the placement,continue, reset or quit?
    if (!playAfterFleetset(grid)){
      return false;
    }
    return true;
  }
  else if (input == "3") 
  {
    StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
    return true;
  }
  else {
    return false;
  }
}


//massive refactoring
bool placing(Grid* grid)
 {

  bool isNotQuit = true;
  std::string input;

  while (isNotQuit) 
  {
    //if fleet is completed
    if (isFleetCompleted(grid)) 
    {
      //do you want to continue, reset or quit?
      if (!playAfterFleetset(grid)) 
      {
        isNotQuit = false;
        break;
      }
      else 
      {
        break;
      }
    }
    //if fleet is not completed
    //how do you want to place a ship and do you want to reset or quit?
    else if (!howToPLaceFleet(grid)) 
    {
      isNotQuit = false;
      break;
    }         
  }
  return isNotQuit;
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
  
  //set type of players
  setPlayersType(StateMachine::getInstance()->getGridPlayer1(), StateMachine::getInstance()->getGridPlayer2(), input);
  
  //player vs computer
  if (input == "1") 
  {
    while(isNotQuit) {
      std::cout << YELLOW << "\nPlayerA set your fleet: \n" << ENDCOLOUR; 
      StateMachine::getInstance()->getGridPlayer1()->renderGrid();     
      
      //keep placing for player or quit?
      if (!placing(StateMachine::getInstance()->getGridPlayer1()))
      {
        isNotQuit = false;
        break;
      }
      else {
        StateMachine::getInstance()->getGridPlayer1()->renderGrid(); 
      }
    }
    if (!isNotQuit) 
    {
      exit();
    }  
    else 
    {
      std::cout << GREEN << "\nComputer placing Fleet...\n\n" << ENDCOLOUR;
      //add a time delay to improve game's pace.
      usleep(2000000);
      automaticallySetFleet(StateMachine::getInstance()->getGridPlayer2());  
    }
        
    
  }  
  else if(input == "2") 
  {
    StateMachine::getInstance()->getGridPlayer1()->setPlayerType("human"); 
    StateMachine::getInstance()->getGridPlayer2()->setPlayerType("human");

      while(true) {
      std::cout << YELLOW << "\nPlayerA set your fleet: \n" << ENDCOLOUR;
      StateMachine::getInstance()->getGridPlayer1()->renderGrid();

      while (true) {
        //if fleet is completed
        if (isFleetCompleted(StateMachine::getInstance()->getGridPlayer1())) 
        {
          //ask what to to next
          input = menuContinue();
          if (input == "1") 
          {
            break;
          }
          else if (input == "2") 
          {
            StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
            StateMachine::getInstance()->getGridPlayer1()->renderGrid();
          }
          else 
          {
            exit();
          }
        }

        //if fleet is not completed
        input = menuSetFleet();
        if (input == "1") {
          manuallySetFleet(StateMachine::getInstance()->getGridPlayer1()); 
        }
        else if (input == "2") 
        {
          automaticallySetFleet(StateMachine::getInstance()->getGridPlayer1());
          StateMachine::getInstance()->getGridPlayer1()->renderGrid();
          input = menuContinue();
          if (input == "2") 
          {
            StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
            StateMachine::getInstance()->getGridPlayer1()->renderGrid();
          }
          else if (input == "1") 
          {
            break;
          }
          else 
          {
            exit();
          }
        }
        else if (input == "3") 
        {
          StateMachine::getInstance()->getGridPlayer1()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer1()->getGrid());
          StateMachine::getInstance()->getGridPlayer1()->renderGrid();
        }
        else {
          exit();
        }
      }
      break;
    }

      while(true) {
      std::cout << YELLOW << "\nPlayerB set your fleet: \n" << ENDCOLOUR;
      StateMachine::getInstance()->getGridPlayer2()->renderGrid();

      while (true) {
        //if fleet is completed
        if (isFleetCompleted(StateMachine::getInstance()->getGridPlayer2())) 
        {
          //ask what to to next
          input = menuContinue();
          if (input == "1") 
          {
            break;
          }
          else if (input == "2") 
          {
            StateMachine::getInstance()->getGridPlayer2()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer2()->getGrid());
          }
          else 
          {
            exit();
          }
        }

        //if fleet is not completed
        input = menuSetFleet();
        if (input == "1") {
          manuallySetFleet(StateMachine::getInstance()->getGridPlayer2()); 
        }
        else if (input == "2") 
        {
          automaticallySetFleet(StateMachine::getInstance()->getGridPlayer2());
          StateMachine::getInstance()->getGridPlayer2()->renderGrid();
          input = menuContinue();
          if (input == "2") 
          {
            StateMachine::getInstance()->getGridPlayer2()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer2()->getGrid());
            StateMachine::getInstance()->getGridPlayer2()->renderGrid();
          }
          else if (input == "1") 
          {
            break;
          }
          else 
          {
            exit();            
          }
        }
        else if (input == "3") 
        {
          StateMachine::getInstance()->getGridPlayer2()->getFleet().resetFleet(StateMachine::getInstance()->getGridPlayer2()->getGrid());
          StateMachine::getInstance()->getGridPlayer2()->renderGrid();
        }
        else {
          exit();
        }
      }
      break;
    }       
  }
  render ();
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