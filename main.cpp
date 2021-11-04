#include <iostream>


#include "headerFiles/StateMachine.h"


int main() 
{    
  StateMachine* gStateMachine = StateMachine::getInstance();
  gStateMachine->change("intro");
  return 0;
}