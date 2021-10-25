#include <iostream>
#include <memory>
#include <regex>
#include <cctype>
#include <math.h> 
#include <string>
#include <set>

#include "headerFiles/constants.h"
#include "headerFiles/Grid.h"
#include "headerFiles/Tile.h"
#include "headerFiles/Ship.h"
#include "headerFiles/Fleet.h"
#include "headerFiles/Utility.h"
#include "headerFiles/Menu.h"
#include "headerFiles/states/BaseState.h"
#include "headerFiles/states/IntroState.h"
#include "headerFiles/states/SetupState.h"
#include "headerFiles/states/PlayState.h"
#include "headerFiles/states/VictoryState.h"
#include "headerFiles/states/GameOverState.h"


int main() 
{  
  Grid gridPlayer;
  manuallySetFleet(gridPlayer);  
  gridPlayer.renderGrid();

  Grid gridComputer; 
  gridComputer.renderGrid();
  automaticallySetFleet(gridComputer);  
  gridComputer.renderGrid();

  // Create and populate a map of the states  
  std::map<std::string, BaseState*> gStateMachine;
  gStateMachine.insert(std::make_pair("intro", new IntroState()));
  gStateMachine.insert(std::make_pair("setup", new SetupState()));
  gStateMachine.insert(std::make_pair("play", new PlayState()));
  gStateMachine.insert(std::make_pair("victory", new VictoryState()));
  gStateMachine.insert(std::make_pair("gameover", new GameOverState()));

  return 0;
}