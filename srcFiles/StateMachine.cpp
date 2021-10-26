#include "../headerFiles/StateMachine.h"
#include "../headerFiles/states/BaseState.h"
#include "../headerFiles/states/IntroState.h"
#include "../headerFiles/states/SetupState.h"
#include "../headerFiles/states/PlayState.h"
#include "../headerFiles/states/VictoryState.h"
#include "../headerFiles/states/GameOverState.h"
#include "../headerFiles/constants.h"

#include <iostream>
#include <map>


//Constructor
StateMachine::StateMachine()
{
  states_.insert(std::make_pair("intro", new IntroState()));
  states_.insert(std::make_pair("setup", new SetupState()));
  states_.insert(std::make_pair("play", new PlayState()));
  states_.insert(std::make_pair("victory", new VictoryState()));
  states_.insert(std::make_pair("gameover", new GameOverState()));

  currentState = states_.find("intro")->second;
  
}
//Destructor
StateMachine::~StateMachine(){}

StateMachine* StateMachine::inst_= nullptr;

//singleton getInstance
StateMachine *StateMachine::getInstance() {
	if(inst_== nullptr){
		inst_ = new StateMachine(); 
	}
	return inst_; 
}

//member methods   
void StateMachine::change(std::string state)
{
  if (!currentState) {
    currentState->exit();
  } else {
    //MAP is a typedef created in 'constants.h';
    MAP::const_iterator iter = states_.find(state);
    if (iter == states_.end()) {
      //handle the error
      std::cout << "\n\033[1;31mState doesn't exist\033[0m\n";
    } else {
    currentState = iter->second;    
    currentState->enter(); //TODO add parameters to pass inside the 'enter' method
    }
  }
}

void StateMachine::update(){}
void StateMachine::render()
{
  currentState->render();
} 