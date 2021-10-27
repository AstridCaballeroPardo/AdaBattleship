#include <iostream>
#include <memory>
#include <regex>
#include <cctype>
#include <math.h> 
#include <string>
#include <set>
#include <map>

#include "headerFiles/constants.h"
#include "headerFiles/Grid.h"
#include "headerFiles/Tile.h"
#include "headerFiles/Ship.h"
#include "headerFiles/Fleet.h"
#include "headerFiles/Utility.h"
#include "headerFiles/Menu.h"
#include "headerFiles/StateMachine.h"


int main() 
{  
  // Grid gridPlayer;
  // manuallySetFleet(gridPlayer);  
  // gridPlayer->renderGrid();

  // Grid gridComputer; 
  // // gridComputer.renderGrid();
  // automaticallySetFleet(gridComputer);  
  // gridComputer->renderGrid();

  // Create object with the states
 
  StateMachine* gStateMachine = StateMachine::getInstance();
  gStateMachine->change("intro");
  

  return 0;
}