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


//Refactoring
int main() 
{  
  Grid grid;   
  
  // manuallySetFleet(grid);

  // grid.renderGrid();
  automaticallySetFleet(grid);  
  grid.renderGrid();
  return 0;
}