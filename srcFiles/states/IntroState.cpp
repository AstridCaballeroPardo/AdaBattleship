#include "../../headerFiles/states/BaseState.h"
#include "../../headerFiles/states/IntroState.h"
#include "../../headerFiles/StateMachine.h"
#include "../../headerFiles/Utility.h"

#include <string>
#include <memory>

std::string input;
std::string msg;

//Constructor
IntroState::IntroState():BaseState() {}
//Destructor
IntroState::~IntroState(){};

//member methods
void IntroState::enter(){}
void IntroState::exit(){}

void IntroState::update()
{
  //get the statemachine
  StateMachine* gStateMachine = StateMachine::getInstance();
  std::cout << "inside update\n";
  gStateMachine->change("setup"); 
}

void IntroState::render()
{
  std::cout << "Welcome to AdaShip! let's play\n\n";
  msg = "press enter to start\n";
  input = userInput(msg);
  if (input.length() == 0) {
    std::cout << input.length() << '\n';
    update();
  }
}