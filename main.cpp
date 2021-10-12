#include <iostream>
#include <memory>
#include <regex>
#include <cctype>

#include "headerFiles/constants.h"
#include "headerFiles/Grid.h"
#include "headerFiles/utility.h"


int main() 
{
  std::string input;  
  udtCoord coord;
  Grid grid; 
  

//Main game loop
  while(true) 
  {
    puts("Enter target X and Y coordinates (e.g. B4): ");
    getline(std::cin, input);
    coord = getXY(input, grid);
  
    //update grid with player's input
    if (validateCoordLimits(coord)){      
      grid.updateGrid(coord.row, coord.column);
      grid.revealGrid();
    }
    else {
      //display message error
      std::cout << "out of boundaries, try again.\n";
    }    
  }

  return 0;
}