#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/GameOverState.h"
#include "../../headerFiles/constants.h"
#include "../../headerFiles/Menu.h"
#include "../../headerFiles/StateMachine.h"

#include <string>
#include <iostream>


//Constructor
GameOverState::GameOverState():BaseState(){}
//Destructor
GameOverState::~GameOverState(){}

//member methods
void GameOverState::enter()
{
  render();
}
void GameOverState::exit(){}
void GameOverState::update()
{
  //transition to intro state
  StateMachine::getInstance()->change("intro"); 
}
void GameOverState::render()
{
  std::cout << "Win!";
  std::cout << RED << "\n\nGame over :(\n\n" << ENDCOLOUR;
  std::string input = menuEndGame();
  if (input.length() == 1) {
    //move to intro state
    update();
  }
}