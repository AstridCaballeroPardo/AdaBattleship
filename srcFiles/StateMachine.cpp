#include "../headerFiles/StateMachine.h"
#include "../headerFiles/states/BaseState.h"
#include "../headerFiles/states/IntroState.h"
#include "../headerFiles/states/SetupState.h"
#include "../headerFiles/states/PlayState.h"
#include "../headerFiles/states/VictoryState.h"
#include "../headerFiles/states/GameOverState.h"
#include "../headerFiles/Utility.h"
#include "../headerFiles/Grid.h"

#include <iostream>
#include <map>



//Constructor
StateMachine::StateMachine():gridPlayer1_(), gridPlayer2_()
{
  states_.insert(std::make_pair("intro", new IntroState()));
  states_.insert(std::make_pair("setup", new SetupState()));
  states_.insert(std::make_pair("play", new PlayState()));
  states_.insert(std::make_pair("victory", new VictoryState()));
  states_.insert(std::make_pair("gameover", new GameOverState()));

  currentState = states_.find("intro")->second; 
  // gridPlayer1_ = new Grid;
  // gridPlayer2_ = new Grid;
  // change("intro");
}
//Destructor
StateMachine::~StateMachine()
{
  delete currentState;
  // delete gridPlayer1_;
  // delete gridPlayer2_;
}

StateMachine* StateMachine::inst_= nullptr;

//singleton getInstance
StateMachine *StateMachine::getInstance() 
{
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
    //MAP is a typedef created in 'Utility.h';
    MAP::const_iterator iter = states_.find(state);
    if (iter == states_.end()) {
      //handle the error
      std::cout << "\n\033[1;31mState doesn't exist\033[0m\n";
    } else {
    currentState = iter->second;
    currentState->enter();
    }
  }
}

void StateMachine::change(std::string state, int params)
{
  if (!currentState) {
    currentState->exit();
  } else {
    //MAP is a typedef created in 'Utility.h';
    MAP::const_iterator iter = states_.find(state);
    if (iter == states_.end()) {
      //handle the error
      std::cout << "\n\033[1;31mState doesn't exist\033[0m\n";
    } else {
    currentState = iter->second;
    currentState->enter(params);
    }
  }
}

void StateMachine::update()
{
  currentState->update();
}
void StateMachine::render()
{
  currentState->render();
} 