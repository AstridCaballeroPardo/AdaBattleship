#include <iostream>
#include <memory>

#include "headerFiles/constants.h"
#include "headerFiles/Grid.h"
#include "headerFiles/utility.h"

int main() 
{

  Grid grid; 

//Main game loop
  // while(true) 
  // {
   
  // }

  grid.updateGrid('A', 1);
  grid.revealGrid();

  grid.updateGrid('E', 5);
  grid.revealGrid();

  return 0;
}