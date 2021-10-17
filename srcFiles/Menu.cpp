#include <iostream>

#include "../headerFiles/Menu.h"
#include "../headerFiles/Grid.h"
#include "../headerFiles/Utility.h"

void menuShipType(){
  std::cout << "\nShip options: \n";
  std::cout << "ID TYPE         SIZE\n";
  std::cout << "1. Carrier        5\n";
  std::cout << "2. Battleship     4\n";
  std::cout << "3. Destroyer      3\n";
  std::cout << "4. Submarine      3\n";
  std::cout << "5. Patrol Boat    2\n";
}

void menuOrientation(){
  std::cout << "\nOrientation options: \n";
  std::cout << "V. Vertical\n";
  std::cout << "H. Horizontal\n";
}

void manuallySetFleet(Grid grid){
  std::string input;  
  std::string msg;
  udtCoordInput coordInput;
  int shipCount =  FLEET_SIZE;  

  while(true) 
  {    
    //display ship options
    menuShipType();

    //display orientation options
    menuOrientation();

    //ask user to input information to set up a ship
    msg = "\nEnter row letter, column number, ship Id and orientation (e.g. B4 1 V): ";
    input = userInput(msg);

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
