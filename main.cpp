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

//refactoring
void manuallySetFleet(Grid grid){
  std::string input;  
  udtCoordInput coordInput;
  int shipCount =  FLEET_SIZE;

  while(true) 
  {    
    //display ship options
    menuShipType();

    //display orientation options
    menuOrientation();

    //get input from player
    puts("\nEnter row letter, column number, ship Id and orientation (e.g. B4 1 V): ");
    getline(std::cin, input);
    //validate input
    if(validateInputFormat(input)){
      coordInput = getParams(input, grid);
  
    //update grid with player's input
      if (validateCoordLimits(coordInput)){      
        grid.updateGrid(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation);
        grid.renderGrid();

        //keep track of placed ships to know when fleet is completed
        shipCount --;       
      

      } else {
      //display message error
      std::cout << "\033[1;31mOut of boundaries! try again.\033[0m\n\n";
      } 
    } else {
      //display message error
      std::cout << "\033[1;31mIncorrect entry, try again (e.g. B4 1 V).\033[0m\n\n";
    } 
    //keep track if fleet is completed
    if (shipCount == 0){
      break;
    }    
  }    
}

int main() 
{
  std::string input;  
  udtCoordInput coordInput;
  int shipCount =  FLEET_SIZE;
  Grid grid;   
  // manuallySetFleet(grid);

//Main game loop
  while(true) 
  {    
    //display ship options
    menuShipType();

    //display orientation options
    menuOrientation();

    //get input from player
    puts("\nEnter row letter, column number, ship Id and orientation (e.g. B4 1 V): ");
    getline(std::cin, input);
    //validate input
    if(validateInputFormat(input)){
      coordInput = getParams(input, grid);
  
    //update grid with player's input
      if (validateCoordLimits(coordInput)){      
        grid.updateGrid(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation);
        grid.renderGrid();

        //keep track of placed ships to know when fleet is completed
        shipCount --; 
      
      // Tile newTile = grid.getTile(coordInput.row, coordInput.column);      
      // std::cout << "row: " << newTile.getX() << '\n';
      // std::cout << "column: " << newTile.getY() << '\n';
      // std::cout << "ship Id: " << newTile.getShipId() << '\n';
      // // std::cout << "ship type: " << newTile.getTileState() << '\n';

      // Fleet fleetPlayer = grid.getFleet();
      // std::vector<Ship>& ships = fleetPlayer.getFleetVector();
      // std::cout << "Grid Id: \n";
      // std::cout << grid.getGridId() << '\n';

      // std::cout << "fleetPlayer: \n";
      // std::cout << "Fleet id: " << fleetPlayer.getGridId() << '\n';
      // std::cout << "Fleet size: " << fleetPlayer.getSize() << '\n';

      // for (int i = 0; i < fleetPlayer.getSize(); i++) {  
      //   std::cout << ships[i].getShipType() << '\n'; 
      // }

      // newTile = grid.getTile(coordInput.row, coordInput.column);      
      // std::cout << "row: " << newTile.getX() << '\n';
      // std::cout << "column: " << newTile.getY() << '\n';
      // std::cout << "ship Id: " << newTile.getShipId() << '\n';

      } else {
      //display message error
      std::cout << "\033[1;31mOut of boundaries! try again.\033[0m\n\n";
      } 
    } else {
      //display message error
      std::cout << "\033[1;31mIncorrect entry, try again (e.g. B4 0 V).\033[0m\n\n";
    } 
    //keep track if fleet is completed
    if (shipCount == 0){
      break;
    }    
  }  

  return 0;
}