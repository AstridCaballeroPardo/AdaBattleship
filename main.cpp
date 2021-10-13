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
//   std::string input;  
//   udtCoord coord;
//   Grid grid; 
  

// //Main game loop
//   while(true) 
//   {
//     puts("Enter target X and Y coordinates (e.g. B4): ");
//     getline(std::cin, input);
//     coord = getXY(input, grid);
  
//     //update grid with player's input
//     if (validateCoordLimits(coord)){      
//       grid.updateGrid(coord.row, coord.column);
//       grid.revealGrid();

      
//       Tile newTile = grid.getTile(coord.row, coord.column);      
//       std::cout << newTile.getX() << '\n';
//       std::cout << newTile.getY() << '\n';
//     }
//     else {
//       //display message error
//       std::cout << "out of boundaries, try again.\n";
//     }    
//   }

  // Tile tileA;
  // std::cout << tileA.getX() << '\n';
  // std::cout << tileA.getY() << '\n';
  // tileA.setX('B');
  // std::cout << tileA.getX() << '\n';
  // std::cout << tileA.getTileState() << '\n';
 

  Ship ship1;  
  std::cout << ship1.getShipId() << '\n';
  Ship ship2;  
  std::cout << ship2.getShipId() << '\n';
  std::cout << ship2.getOrientation() << '\n';

  ship2.setShip((int)shipType::carrier, (int)shipOrientation::vertical);
  std::cout << '\n' << ship2.getShipType() << '\n';
  std::cout << ship2.getShipLen() << '\n';
  std::cout << ship2.getOrientation() << '\n';

  return 0;
}