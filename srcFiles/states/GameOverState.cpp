
#include <string>
#include <iostream>

#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/GameOverState.h"
#include "../../headerFiles/constants.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"

//Constructor
GameOverState::GameOverState():BaseState(){}
//Destructor
GameOverState::~GameOverState(){}

//member methods
void GameOverState::enter()
{
  exit();
}
void GameOverState::exit()
{
  //clean
  Grid& grid1 = StateMachine::getInstance()->getGridPlayer1();
  Grid& grid2 = StateMachine::getInstance()->getGridPlayer2();      

  std::vector<int>& bombedTilesGrid1 = StateMachine::getInstance()->getBombedTilesGrid1();
  std::vector<int>& bombedTilesGrid2 = StateMachine::getInstance()->getBombedTilesGrid1();

  //reset ships
  grid1.resetFleet();
  //reset bombed empty tiles 
  grid1.resetBombedTiles(bombedTilesGrid1);
  
  //reset ships
  grid2.resetFleet();
  //reset bombed empty tiles 
  grid2.resetBombedTiles(bombedTilesGrid2);
  
  render();
}
void GameOverState::update()
{
  //transition to intro state
  StateMachine::getInstance()->change("intro"); 
}
void GameOverState::render()
{  
  std::cout << RED << "\n\nGame over :( \n\n" << ENDCOLOUR;
  std::cout << "\n\nyou will do better next time ;)\n\n";
  std::string input = menuEndGame();
  if (input == "1") {
    //move to intro state
    update();
  }
}