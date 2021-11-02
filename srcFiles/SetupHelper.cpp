
#include <math.h>
#include <numeric>

#include "../headerFiles/SetupHelper.h"
#include "../headerFiles/Utility.h"
#include "../headerFiles/Menu.h"
#include "../headerFiles/Validation.h"

//refactoring
// void setupPlacingShip(int len, int availableTiles_, udtCoordInput coordInput, int randomIndex, int gridSize, std::vector<int> unplacedShipsVect, int& i, Grid& grid, std::set<int> indexSet)
// {
//   //setup the ship
//   // if (!(availableTiles_ == len)) 
//   // {
//   //   return;
//   // }       
//   coordInput.row = intToLetter((randomIndex / gridSize));
//   coordInput.column = (randomIndex % gridSize);
//   coordInput.shipType = unplacedShipsVect[i];

//   //update grid with player's input                       
//   if(grid.placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation, randomIndex)) 
//   {
//     //keep track of placed ships to know when fleet is completed           
//     i++;

//     // remove values from set(the one with values from 0 to GRID_SIZE)
//     removeValueSet(coordInput.orientation, randomIndex, gridSize, indexSet, len);
            
//   }
// }
 



void manuallySetFleet(Grid& grid)
{
  std::string input;  
  std::string msg;
  udtCoordInput coordInput;   
  int shipCount =grid.getFleet().getSize(); 
  int totalTiles = pow(grid.getSize(), 2);
  int availableTiles_ = 0;
  int gridSize = grid.getSize();
  int len = 0;
  std::vector<Ship>& ships = grid.getFleet().getFleetVector();


  //create set with values form 0 to GRID_SIZE (side's size), they will represent the location of the elements (tiles) in the grid    
  std::set<int> indexSet = createSet(totalTiles); 

  //create vetor unplacedShipsVect with numbers from zero to five
  std::vector<int> unplacedShipsVect(shipCount);
  //iota, "Fills the range [first, last) with sequentially increasing values, starting with value and repetitively evaluating ++value" https://en.cppreference.com/w/cpp/algorithm/iota
  std::iota (std::begin(unplacedShipsVect), std::end(unplacedShipsVect), 1);
  
  //Get unplaced ships and update indexSet
  getUnplacedShips(grid, shipCount, unplacedShipsVect, gridSize, indexSet);

  //update number of ships to be placed
  shipCount = unplacedShipsVect.size();

  while(true) 
  {  
    //display ship options
    menuShipType(ships);

    //display orientation options
    menuOrientation(); 

    //ask user to input information to set up a ship
    msg = "\nEnter row letter, column number, ship Id and orientation (e.g. B4 1 V): ";
    input = userInput(msg);    

    //validate input
    if(!validateInputFormat(input)) 
    {
      //display message error
      std::cout << "\033[1;31mIncorrect entry, try again (e.g. B4 1 V).\033[0m\n\n";
      continue;
    }
    // if(validateInputFormat(input)){
    coordInput = getParams(input, REGEXPLACESHIP);

    len = calcShipLength(coordInput.shipType); 

    //calculate index value ((row * length of grid's side) + col)   
    int indVal = userInputToIndex(coordInput.row, coordInput.column, gridSize); 
    availableTiles_ = 0;

    //check if target index is in set(find is O(log n))
    if (!(indexSet.find(indVal) != indexSet.end() && validateBounds(coordInput.row, coordInput.column, gridSize))) 
    {
      //display message error
      std::cout << "\033[1;31mShip can't be placed try again.\033[0m\n\n";
      continue;
    }
    
    availableTiles_++;

    //check number of tiles available in the set collection
    availableTiles_ += availableTiles(coordInput.orientation, indVal, gridSize, indexSet, len);

    //update grid with player's input  
    if (!(availableTiles_ == len))  
    {
      //display message error
      std::cout << "\033[1;31mShip can't be placed try again.\033[0m\n\n";
      continue;
    }          
      // if (availableTiles_ == len){      
    if(grid.placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation, indVal)) {
      // grid->renderGrid(); 
      //keep track of placed ships to know when fleet is completed
      shipCount --; 
      
      // remove values from set(the one with values from 0 to GRID_SIZE)
      removeValueSet(coordInput.orientation, indVal, gridSize, indexSet, len);
      break;
    } 
    //keep track if fleet is completed
    if (shipCount == 0){
      grid.renderGrid();
      menuShipType(ships);
      std::cout << "\n\033[1;32mAll ships placed!\033[0m\n\n";        
      break;
    } 
  } 
}

void getUnplacedShips(Grid& grid, int shipCount, std::vector<int>& unplacedShipsVect, int gridSize, std::set<int>& indexSet)
{
    //check if shipType[i] != 0
  for (int i = 0; i < shipCount; i++) 
  {
    Ship tmpShip = grid.getFleet().getFleetVector()[i];
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

void automaticallySetFleet(Grid& grid) 
{
  int totalTiles = pow(grid.getSize(), 2);
  int shipCount = grid.getFleet().getSize();
  udtCoordInput coordInput; 
  int randomIndex = 0;
  int gridSize = grid.getSize();
  int len = 0;
  int availableTiles_ = 0; 
  

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
    if (!(indexSet.find(randomIndex) != indexSet.end())) 
    {
      continue;
    }
    // if (indexSet.find(randomIndex) != indexSet.end()){
    availableTiles_++;

    //get random orientation 
    coordInput.orientation = orientationIntToChar(randomVal( 1, 2));

    //check number of tiles available
    availableTiles_ += availableTiles(coordInput.orientation, randomIndex, gridSize, indexSet, len);

      //setup the ship
      if (availableTiles_ == len) 
      {        
        coordInput.row = intToLetter((randomIndex / gridSize));
        coordInput.column = (randomIndex % gridSize);
        coordInput.shipType = unplacedShipsVect[i];
      
        //update grid with player's input                       
        if(grid.placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation, randomIndex)) {
          //keep track of placed ships to know when fleet is completed           
          i++;

          // remove values from set(the one with values from 0 to GRID_SIZE)
          removeValueSet(coordInput.orientation, randomIndex, gridSize, indexSet, len);
                  
        }
      } 
      else {
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
          if(grid.placeShip(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation, randomIndex)) {
            //keep track of placed ships to know when fleet is completed
            i++;

            // remove values from set(the one with values from 0 to GRID_SIZE)
            removeValueSet(coordInput.orientation, randomIndex, gridSize, indexSet, len);  
          }
        }         
      }
    // }
  }  
} 

void placing(Grid& grid)
{
 std::string input;
 input = menuSetFleet();
 if (input == "1")
 {
   manuallySetFleet(grid);
 }
 else if (input == "2")
 {
   automaticallySetFleet(grid);    
 }
}
 
void playerTurn(Grid& grid)
{
 //keep placing for player or quit?
 grid.renderGrid();
 placing(grid);
 grid.renderGrid();
}
 
void setPlayersType(Grid& gridPlayer1, Grid& gridPlayer2, std::string type) {
 if (type == "1") {
   gridPlayer1.setPlayerType("human");
   gridPlayer2.setPlayerType("computer");
 }
 else if (type == "2") {
   gridPlayer1.setPlayerType("human");
   gridPlayer2.setPlayerType("human");
 }
}

void playerTurnLoop(Grid& grid, bool& isNotQuit, char playerLabel) { 
 while(!grid.getFleet().isFleetCompleted()) {
         
     std::cout << YELLOW << "\nPlayer" << playerLabel << " set your fleet: \n" << ENDCOLOUR;
    
     playerTurn(grid);
         
     isNotQuit = continueResetQuit(grid);
     if(!isNotQuit) {
       break;
     }
   }
}