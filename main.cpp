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
  Grid gridPlayer;
  manuallySetFleet(gridPlayer);
  // automaticallySetFleet(gridPlayer);
  gridPlayer.renderGrid();

  Grid gridComputer; 
  automaticallySetFleet(gridComputer);  
  gridComputer.renderGrid();

  int shipIndex = 0;
  int shipLen = 0;
  char shipOrientation = ' ';
  

 // check player info 
  std::cout << "\033[1;32mPlayer's Fleet:\033[0m\n";
  std::cout << "grid's id: " << gridPlayer.getGridId() << '\n';
  Fleet gridFleetPlayer = gridPlayer.getFleet(); 
  std::vector<Ship>& shipsPlayer = gridFleetPlayer.getFleetVector();
  for (int i = 0, count = 0; i < shipsPlayer.size(); i++) {  
      std::cout << '\n';    
        //find ship
        shipIndex = shipsPlayer[i].getShipIndex();
        udtCoordInput xy = indexToXY(shipIndex, gridPlayer.getSize());
        int x = letterToInt(xy.row);
        int y = xy.column;
        shipLen = shipsPlayer[i].getShipLen();     
        shipOrientation = shipsPlayer[i].getOrientation(); 

        std::cout << "Ship orientation: " <<  shipOrientation << '\n'; 
        std::cout << "Ship length: " <<  shipLen << '\n'; 
        std::cout << "Ship type: " <<  shipsPlayer[i].getShipType() << '\n'; 
        
        //access fleet's tiles
        for (int n = 0; n < shipLen; n++) {
         
         if (shipOrientation == 'H') {
          
          Tile& newTile = gridPlayer.getGrid()[x][y + n]; 
          std::cout << "row: " << newTile.getX() << '\n';
          std::cout << "column: " << newTile.getY() << '\n';
          std::cout << "ship Id: " << newTile.getShipId() << '\n';
          std::cout << "ship TileState: " << newTile.getTileState() << '\n';
          std::cout << "ship symbol: " << newTile.getIcon() << '\n';            
          } else if (shipOrientation == 'V') {

          Tile& newTile = gridPlayer.getGrid()[x + n][y]; 

          std::cout << "row: " << newTile.getX() << '\n';
          std::cout << "column: " << newTile.getY() << '\n';
          std::cout << "ship Id: " << newTile.getShipId() << '\n';
          std::cout << "ship TileState: " << newTile.getTileState() << '\n';
          std::cout << "ship symbol: " << newTile.getIcon() << '\n';
        }
    }
  }

  std::cout << '\n';
  
  // check computer info 
  std::cout << "\033[1;32mComputer's Fleet:\033[0m\n";
  std::cout << "grid's id: " << gridComputer.getGridId() << '\n';
  Fleet gridFleetComputer = gridComputer.getFleet(); 
  std::vector<Ship>& shipsComputer = gridFleetComputer.getFleetVector();
  for (int i = 0, count = 0; i < shipsPlayer.size(); i++) {  
      std::cout << '\n';    
        //find ship
        shipIndex = shipsComputer[i].getShipIndex();
        udtCoordInput xy = indexToXY(shipIndex, gridComputer.getSize());
        int x = letterToInt(xy.row);
        int y = xy.column;
        shipLen = shipsComputer[i].getShipLen();     
        shipOrientation = shipsComputer[i].getOrientation(); 

        std::cout << "Ship orientation: " <<  shipOrientation << '\n'; 
        std::cout << "Ship length: " <<  shipLen << '\n'; 
        std::cout << "Ship type: " <<  shipsComputer[i].getShipType() << '\n'; 
        
        //access fleet's tiles
        for (int n = 0; n < shipLen; n++) {
         
         if (shipOrientation == 'H') {
          
          Tile& newTile = gridComputer.getGrid()[x][y + n]; 
          std::cout << "row: " << newTile.getX() << '\n';
          std::cout << "column: " << newTile.getY() << '\n';
          std::cout << "ship Id: " << newTile.getShipId() << '\n';
          std::cout << "ship TileState: " << newTile.getTileState() << '\n';
          std::cout << "ship symbol: " << newTile.getIcon() << '\n';            
          } else if (shipOrientation == 'V') {

          Tile& newTile = gridComputer.getGrid()[x + n][y]; 

          std::cout << "row: " << newTile.getX() << '\n';
          std::cout << "column: " << newTile.getY() << '\n';
          std::cout << "ship Id: " << newTile.getShipId() << '\n';
          std::cout << "ship TileState: " << newTile.getTileState() << '\n';
          std::cout << "ship symbol: " << newTile.getIcon() << '\n';
        }
    }
  }
  return 0;
}