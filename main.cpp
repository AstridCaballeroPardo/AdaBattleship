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


int main() 
{  
  Grid gridPlayer;
  manuallySetFleet(gridPlayer);  
  gridPlayer.renderGrid();

  Grid gridComputer; 
  gridComputer.renderGrid();
  automaticallySetFleet(gridComputer);  
  gridComputer.renderGrid();

  return 0;
}