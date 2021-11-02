#include <iostream>
#include <ostream>
#include <math.h> 
#include <vector>
#include <iomanip>
#include <string>
#include <numeric>
#include <algorithm>

#include "../headerFiles/Menu.h"
#include "../headerFiles/Grid.h"
#include "../headerFiles/Ship.h"
#include "../headerFiles/Utility.h"
#include "../headerFiles/constants.h"

void shipTextToPrint(int shipType, std::string shipTypeStr, std::string msg)
{
  std::cout << std::setfill(' ') << std::setw(2) << shipType << "  " << std::setw(11) << shipTypeStr << "  " << std::setw(4)  << calcShipLength(shipType) << "  " <<  msg;
}

std::string getMsg(std::vector<Ship>& ships, int i)
{
  std::string msg;
  for (int j = 0; j < ships.size(); j++) {
      if (ships[j].getShipType() == i) {
        if(!ships[j].getIsSunk()){
          msg = "placed\n";
          break;
        }
        else {
          msg = "sunk\n";
          break;
        }
      }
      else {
        msg = "not placed\n";
      }
    }
    return msg;
}

void menuShipType(std::vector<Ship>& ships) {
  std::cout << "\nShip options: \n";
  //print headers
  std::cout << std::setfill(' ') << std::setw(2) << "ID" << "  " << std::setw(11) << "TYPE    "  << "  " << std::setw(4) << "SIZE" << "  " << "STATE\n";
  
  for (int i = 1; i <= ships.size(); i++) 
  {
    std::string shipTypeStr = getStringForEnum(i);
    //find the ship with shipType == i
    std::string msg = getMsg(ships, i); 
    
    shipTextToPrint(i, shipTypeStr, msg);
  }
}

void menuOrientation()
{
  std::cout << "\nOrientation options: \n";
  std::cout << "V. Vertical\n";
  std::cout << "H. Horizontal\n";
}

void manuallySetFleet(Grid* grid)
{
  std::string input;  
  std::string msg;
  udtCoordInput coordInput;   
  int shipCount =grid->getFleet().getSize(); 
  int totalTiles = pow(grid->getSize(), 2);
  int availableTiles_ = 0;
  int gridSize = grid->getSize();
  int len = 0;
  std::vector<Ship>& ships = grid->getFleet().getFleetVector();


  //create set with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid    
  std::set<int> indexSet = createSet(totalTiles); 

  //create vetor unplacedShipsVect with numbers from zero to five
  std::vector<int> unplacedShipsVect(shipCount);
  std::iota (std::begin(unplacedShipsVect), std::end(unplacedShipsVect), 1);
  
  //Get unplaced ships and update indexSet
  getUnplacedShips(grid, shipCount, unplacedShipsVect, gridSize, indexSet);

  //update number of ships to be placed
  shipCount = unplacedShipsVect.size();

  while(true) 
  {    
    //display grid
    // grid->renderGrid(); 

    //display ship options
    menuShipType(ships);

    //display orientation options
    menuOrientation(); 

    //ask user to input information to set up a ship
    msg = "\nEnter row letter, column number, ship Id and orientation (e.g. B4 1 V): ";
    input = userInput(msg);    

    //validate input
    if(validateInputFormat(input)){
      coordInput = getParams(input, REGEXPLACESHIP);

      len = calcShipLength(coordInput.shipType); 

      //calculate index value ((row * length of grid's side) + col)
      int indVal = ((coordInput.row - CAPITAL_LETTER)  * gridSize) + coordInput.column;
      availableTiles_ = 0;

      //check if target index is in set(find is O(log n))
      if (indexSet.find(indVal) != indexSet.end()){
      availableTiles_++;

      //check number of tiles available in the set collection
      availableTiles_ += availableTiles(coordInput.orientation, indVal, gridSize, indexSet, len);
  
      //update grid with player's input        
        if (availableTiles_ == len){      
          if(grid->placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation, indVal)) {
            // grid->renderGrid(); 
            //keep track of placed ships to know when fleet is completed
            shipCount --; 
            
            // remove values from set(the one with values from 0 to GRID_SIZE)
            removeValueSet(coordInput.orientation, indVal, gridSize, indexSet, len);
            break;
          } 

        } else {
        //display message error
        std::cout << "\033[1;31mShip can't be placed try again.\033[0m\n\n";
        } 
      } else {
        //display message error
        std::cout << "\033[1;31mShip can't be placed try again.\033[0m\n\n";
        } 
      //keep track if fleet is completed
      if (shipCount == 0){
        grid->renderGrid();
        menuShipType(ships);
        std::cout << "\n\033[1;32mAll ships placed!\033[0m\n\n";        
        break;
      }    
    } else {
      //display message error
      std::cout << "\033[1;31mIncorrect entry, try again (e.g. B4 1 V).\033[0m\n\n";
    }     
  } 
}

void getUnplacedShips(Grid* grid, int shipCount, std::vector<int>& unplacedShipsVect, int gridSize, std::set<int>& indexSet)
{
    //check if shipType[i] != 0
  for (int i = 0; i < shipCount; i++) 
  {
    Ship tmpShip = grid->getFleet().getFleetVector()[i];
    int shipType = tmpShip.getShipType();
    if(shipType != 0) 
    {
      //remove shiptype from placedShipsVect
      unplacedShipsVect.erase(std::remove(unplacedShipsVect.begin(), unplacedShipsVect.end(), shipType), unplacedShipsVect.end());      
      //get index and orientation and type(to calculate len) from ship
      int len = calcShipLength(shipType);
      //delete indexes from indexSet
      removeValueSet(tmpShip.getOrientation(), tmpShip.getShipIndex(), gridSize, indexSet, len); 
    }
    else {
      break;
    }  
  }
}

void automaticallySetFleet(Grid* grid) 
{
  int totalTiles = pow(grid->getSize(), 2);
  int shipCount = grid->getFleet().getSize();
  udtCoordInput coordInput; 
  int randomIndex = 0;
  int gridSize = grid->getSize();
  int len = 0;
  int availableTiles_ = 0;
  // int shipTypeIt = 0;
  // int firstEmptyShip = 0;
  

  //create set with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid
  std::set<int> indexSet = createSet(totalTiles); 
  //create vetor unplacedShipsVect with numbers from zero to five
  std::vector<int> unplacedShipsVect(shipCount);
  std::iota (std::begin(unplacedShipsVect), std::end(unplacedShipsVect), 1);
  
  //Get unplaced ships
  getUnplacedShips(grid, shipCount, unplacedShipsVect, gridSize, indexSet);
  
  //update number of ships to be placed
  shipCount = unplacedShipsVect.size();
  
  //main loop to place the ships  
  for(int i = 0; i < unplacedShipsVect.size(); )
  { 
  // while (shipTypeIt != shipCount + 1) {
    
    len = calcShipLength(unplacedShipsVect[i]); 
    availableTiles_ = 0;

    //get random index based on set size
    randomIndex = randomVal(0, totalTiles - 1);    

    //check random index is in set(find is O(log n))
    if (indexSet.find(randomIndex) != indexSet.end()){
      availableTiles_++;

      //get random orientation 
      coordInput.orientation = orientationIntToChar(randomVal( 1, 2));

      //check number of tiles available
      availableTiles_ += availableTiles(coordInput.orientation, randomIndex, gridSize, indexSet, len);

      //setup the ship
      if (availableTiles_ == len) {        
        coordInput.row = intToLetter((randomIndex / gridSize));
        coordInput.column = (randomIndex % gridSize);

        coordInput.shipType = unplacedShipsVect[i];
      
        //update grid with player's input                       
        if(grid->placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation, randomIndex)) {
          //keep track of placed ships to know when fleet is completed           
          i++;

          // remove values from set(the one with values from 0 to GRID_SIZE)
          removeValueSet(coordInput.orientation, randomIndex, gridSize, indexSet, len);
                  
        }
      } else {
        //try the other orientation
        availableTiles_ = 1;        
        coordInput.orientation = coordInput.orientation == 'H' ? 'V':'H';

        //check number of tiles available
        availableTiles_ += availableTiles(coordInput.orientation, randomIndex, gridSize, indexSet, len);
        
        if(availableTiles_ == len) {
          coordInput.row = intToLetter((randomIndex / gridSize));
          coordInput.column = (randomIndex % gridSize);
          coordInput.shipType = unplacedShipsVect[i];
      
          //update grid with player's input                       
          if(grid->placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation, randomIndex)) {
            //keep track of placed ships to know when fleet is completed
            i++;

            // remove values from set(the one with values from 0 to GRID_SIZE)
            removeValueSet(coordInput.orientation, randomIndex, gridSize, indexSet, len);  
          }
        }         
      }
    }
  }  
} 

std::string menuContinue()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENURESET))
  {
    std::string msg = "\nSelect:\n1.continue\n2.reset\n0.quit\n";
    input = userInput(msg);
  }
  
  return input;
}

std::string menuTransToPlay()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUTRANSTOPLAY))
  {
  std::string msg = "\nReady to play?:\n1.OK\n0.quit\n";
  input = userInput(msg);
  }
  return input;
}

std::string menuTurn()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUTURN))
  {
  std::string msg = "\nSelect:\n1.End turn\n0.quit\n";
  input = userInput(msg);
  }
  return input;
}

std::string menuSetFleet()
{
   std::string input = " ";
    while(!validateInputMenu(input, MENUSETMODE))
    {
    std::string msg = "\n1.Manually\n2.Auto-place\n";
    input = userInput(msg);
    }
    return input;
}


std::string menuEndGame()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUTURN))
  {
  std::string msg = "\npress:\n1.start new game\n0.quit\n";
  input = userInput(msg);
  }
  return input;
}


std::string menuGameType()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENURESET))
  {
    std::cout << YELLOW << "\n\nLet's play :)\n" << ENDCOLOUR;
    std::string msg = "\n\nSelect from the menu: \n1. One player vs computer game\n2. Two player game\n0. Quit\n";
    input = userInput(msg);
  }
  return input;
}


std::string menuEntry()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUENTRY))
  {
    std::cout << YELLOW << "\n\nWelcome to AdaShip!\n\n" << ENDCOLOUR;
    std::string msg = "Select:\n1.Start\n0.Exit game\n";
    input = userInput(msg);
  }
  return input;
}

std::string menuShoot()
{
   std::string input = " ";
    while(!validateInputMenu(input, MENUSETMODE))
    {
    std::string msg = "\n1.Manually\n2.Auto-fire\n";
    input = userInput(msg);
    }
    return input;
}