
#include <unistd.h>
#include <math.h>

#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/SetupState.h"
#include "../../headerFiles/Grid.h"
#include "../../headerFiles/Fleet.h"
#include "../../headerFiles/Tile.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"
#include "../../headerFiles/SetupHelper.h"


//Constructor
SetupState::SetupState():BaseState(){}
//Destructor
SetupState::~SetupState(){}

//member methods
void SetupState::enter()
{
  char playerLabel = ' ';
  bool isNotQuit = true;
  bool hide = false;
  
  //ask type of game to play
  std::string input;

  input = menuGameType();

  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  
  //set type of players human/computer
  setPlayersType(grid1, grid2, input);
  
  //player vs computer
  if (input == "1") 
  {
    playerLabel ='A';
    playerTurnLoop(grid1, isNotQuit, playerLabel, hide);
    
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
      automaticallySetFleet(grid2);  
      render ();
    }  
  }  
  else if(input == "2") 
  {
    playerLabel ='A';
    playerTurnLoop(grid1, isNotQuit, playerLabel, hide);
    
    if (!isNotQuit) 
    {
      exit();
    }  
    //next player
    else 
    {
      playerLabel ='B';
      playerTurnLoop(grid2, isNotQuit, playerLabel, hide);

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
  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();
  // transition back to intro
  grid1.resetFleet();
  
  grid2.resetFleet();
  
  StateMachine::getInstance()->change("intro"); 
}
void SetupState::update()
{
  //transition to next state
  StateMachine::getInstance()->change("play"); 
}
void SetupState::render()
{
  std::string inputMenuToPlay = menuTransToPlay();
  if (inputMenuToPlay == "1") {
    //move to the play state
    update();
  }
  else {
    exit();
  }
}