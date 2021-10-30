#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/IntroState.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"

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
  std::string input;
  std::string msg;
  std::cout << YELLOW << "\n\nWelcome to AdaShip! let's play :)\n\n" << ENDCOLOUR;
  msg = "press enter to start or 0 to exit game\n";
  input = userInput(msg);
  if (input.length() == 0) {
    //move to setup state
    update();
  }
  else 
  {
    exit();
  }
}