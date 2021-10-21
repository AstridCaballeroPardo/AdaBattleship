#include <iostream>
#include <math.h> 

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

void manuallySetFleet(Grid& grid){
  std::string input;  
  std::string msg;
  udtCoordInput coordInput;   
  int shipCount =grid.getFleet().getSize(); 

  while(true) 
  {    
    //display grid
    grid.renderGrid(); 

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
      if (validateCoordLimits(coordInput, grid.getSize())){      
        if(grid.placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation)) {
          //keep track of placed ships to know when fleet is completed
          shipCount --; 
        }     

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
      std::cout << "\033[1;31mIncorrect entry, try again (e.g. B4 1 V).\033[0m\n\n";
    }     

    //keep track if fleet is completed
    if (shipCount == 0){
      std::cout << "\033[1;32mAll ships placed!\033[0m\n\n";
      break;
    }    
  }    
}

void automaticallySetFleet(Grid& grid){
  int totalTiles = pow(grid.getSize(), 2);
  int shipCount = grid.getFleet().getSize();
  udtCoordInput coordInput; 
  int randomIndex = 0;
  int gridSize = grid.getSize();
  int len = 0;
  int availableTiles_ = 0;
  

  //create set with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid
  std::set<int> index = createSet(totalTiles); 

  //main loop to place the ships
  while (shipCount != 0) {   
    //claculate len per ship
    len = calcShipLength(shipCount); 
    availableTiles_ = 0;

    //get random index based on set size
    randomIndex = randomVal(0, totalTiles - 1);
    std::cout << "random index: " << randomIndex << std::endl;

    //check random index is in set(find is O(log n))
    if (index.find(randomIndex) != index.end()){
      availableTiles_++;

      //get random orientation 
      coordInput.orientation = orientationIntToChar(randomVal( 1, 2));

      //check number of tiles available
      availableTiles_ += availableTiles(coordInput.orientation, randomIndex, gridSize, index, len);

      //setup the ship
      if (availableTiles_ == len) {        
        coordInput.row = intToLetter((randomIndex / gridSize));
        coordInput.column = (randomIndex % gridSize) + 1;
        coordInput.shipType = shipCount;
      
        //update grid with player's input                       
        if(grid.placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation)) {
          //keep track of placed ships to know when fleet is completed
          shipCount --; 

          // remove values from set(the one with values from 0 to GRID_SIZE)
          removeValueSet(coordInput.orientation, randomIndex, gridSize, index, len);
          //print index set after removing elements
          std::cout << "size of index set: " << index.size() << '\n';          
        }
      } else {
        //display message error
        std::cout << "\033[1;31mOut of boundaries! try again.\033[0m\n\n";
      }
    }
  }  
}
