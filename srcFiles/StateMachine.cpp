#include "../headerFiles/StateMachine.h"
#include "../headerFiles/states/BaseState.h"

#include <iostream>



//Constructor
StateMachine::StateMachine(std::map<std::string, BaseState*> states):currentState()
{
  states_ = states;
}
//Destructor
StateMachine::~StateMachine(){};

//member methods   
void StateMachine::change(BaseState* state)
{
  if (!currentState) {
    currentState.exit();
  }
 currentState = state;
 currentState->enter(); //add parameters to pass inside the 'enter' method
}

void StateMachine::update(){};
void StateMachine::render(){}; 