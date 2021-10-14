#include <iostream>
#include <memory>
#include <regex>
#include <cctype>

#include "headerFiles/constants.h"
#include "headerFiles/Grid.h"
#include "headerFiles/Tile.h"
#include "headerFiles/Ship.h"
#include "headerFiles/Utility.h"


int main() 
{
  std::string input;  
  udtCoordInput coordInput;
  Grid grid; 
  

//Main game loop
  while(true) 
  {
    puts("Enter ship information: X, Y, type and orientation (e.g. B4 0 v): ");
    getline(std::cin, input);
    coordInput = getParams(input, grid);
  
    //update grid with player's input
    if (validateCoordLimits(coordInput)){      
      grid.updateGrid(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation);
      grid.revealGrid();

      
      Tile newTile = grid.getTile(coordInput.row, coordInput.column);      
      std::cout << "row: " << newTile.getX() << '\n';
      std::cout << "column: " << newTile.getY() << '\n';
      std::cout << "ship Id: " << newTile.getShipId() << '\n';

      newTile = grid.getTile(coordInput.row, coordInput.column + 1);      
      std::cout << "Tile to the right\n";
      std::cout << "row: " << newTile.getX() << '\n';
      std::cout << "column: " << newTile.getY() << '\n';
      std::cout << "ship Id: " << newTile.getShipId() << '\n';

      newTile = grid.getTile(coordInput.row + 1, coordInput.column);   
      std::cout << "Tile below\n";   
      std::cout << "row: " << newTile.getX() << '\n';
      std::cout << "column: " << newTile.getY() << '\n';
      std::cout << "ship Id: " << newTile.getShipId() << '\n';
    } else {
      //display message error
      std::cout << "out of boundaries, try again.\n";
    }    
  }  

  return 0;
}