#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/IntroState.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"
#include "../../headerFiles/Menu.h"

#include <string>
#include <memory>

//Constructor
IntroState::IntroState():BaseState() {}
//Destructor
IntroState::~IntroState(){}

//member methods
void IntroState::enter()
{
  render();
}
void IntroState::exit()
{
  std::exit(0);
}

void IntroState::update()
{    
  //transition to next state
  StateMachine::getInstance()->change("setup"); 
}

void IntroState::render()
{
  std::string input = menuEntry();
  if (input == "1") {
    //move to setup state
    update();
  }
  else 
  {
    exit();
  }
}