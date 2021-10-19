#include <iostream>
#include <memory>
#include <regex>
#include <cctype>

#include "headerFiles/constants.h"
#include "headerFiles/Grid.h"
#include "headerFiles/Tile.h"
#include "headerFiles/Ship.h"
#include "headerFiles/Fleet.h"
#include "headerFiles/Utility.h"
#include "headerFiles/Menu.h"


int main() 
{  
  Grid grid(5);   
  manuallySetFleet(grid);

  //create vector with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid
  // std::vector<int> index;
  // for (int i = 0; i < grid.getSize(); )
  //main loop to automatically place ships
    //get random index based on vector size
    //get random orientation
    //loop trhought the fleet to place one ship at the time
    //from the ship type that will be placed get len
    //check if there is space (see if I can reuse "areTilesAvailable" function)
    // if so
        // place ship
        // remove values from vector(the one with values from 0 to GRID_SIZE)

  return 0;
}