#include <vector>
#include <unistd.h>
#include <random>


#include "../headerFiles/constants.h"
#include "../headerFiles/Grid.h"
#include "../headerFiles/Menu.h"
#include "../headerFiles/Utility.h"
#include "../headerFiles/Validation.h"
#include "../headerFiles/PlayHelper.h"

void playerShoot(std::vector<int>& indexVectPlayer, int valIndex, int gridSize, udtCoordInput coordInput, Grid& gridPlayer, bool isAutofired)
{
  int shipTargetId;
  int tileTargetState;
  int x;
  //check random index is in set(find is O(log n))  
  if (isAutofired) {
    x = (valIndex / gridSize);            
    coordInput.column = (valIndex % gridSize);
  } 
  else if (!isAutofired)
  {
    x = letterToInt(coordInput.row);
  }

  //go to targeted tile
  std::vector<std::vector<Tile>>& grid = gridPlayer.getGrid();
  Tile& tileTarget = grid[x][coordInput.column];
  tileTargetState = tileTarget.getTileState();

  if (tileTargetState == 1) 
  {
    //Update tile. change tileState and icon              
    tileTarget.setTileState((int)tileState::bombedTile);
    tileTarget.setIcon('X');

    //identify shipId from tile
    shipTargetId = tileTarget.getShipId();
    
    //find ship in fleet
    std::vector<Ship>& ships = gridPlayer.getFleet().getFleetVector();              
    Ship& shipTarget = gridPlayer.getFleet().getShip(ships, shipTargetId);
    
    shipTarget.reduceShipLen();

    //update fleet if ship is sunk
    if (shipTarget.getShipLen() == 0)
    {
      shipTarget.setIsSunk(true);
      std::cout << "\033[1;32mShip is sunk!\033[0m\n";

      Fleet& fleet = gridPlayer.getFleet();
      fleet.reduceFleetSize();
      
      if (fleet.getSize() == 0) 
      {
        std::cout << "\033[1;32mFleet is sunk!\033[0m\n";            
      } 
    }      
  } 
  else if (tileTargetState == 0) 
  {
    //Update tile. change tileState and icon
    tileTarget.setTileState((int)tileState::bombedTile);              
  }    
  removeTarjetVector(valIndex, indexVectPlayer);    

  //end of players's turn
  //display player's grid
  gridPlayer.renderGrid(); 
}

void autoFire(std::vector<int>& indexVecPlayer, int gridSize, udtCoordInput coordInput, Grid& grid, std::vector<int>& bombedTilesGrid, bool& isNotQuit) 
{
  //get random index based on set size
  int randomIndex = randomVal(0, indexVecPlayer.size() - 1); 
  //get value at randomIndex
  int valAtRandomIndx = indexVecPlayer[randomIndex];
  
  playerShoot(indexVecPlayer, valAtRandomIndx, gridSize, coordInput, grid, true);
  //keep track of bombed tiles         
  bombedTilesGrid.push_back(valAtRandomIndx);                  
  //user ends turn or quits game
  std::string input = menuTurn();
  if (input == "0") {
    isNotQuit = false;            
  } 
}

void manualShoot(udtCoordInput coordInput, int indVal, int gridSize, std::vector<int>& indexVecPlayer, std::vector<int>& bombedTilesGrid, bool& isNotQuit, Grid& grid) 
{
  while (true) 
  {  
    std::string input;
    std::string msg;
    msg = "\nEnter row letter, column number(e.g. B4): ";
    input = userInput(msg);
    //validate input
    if(!validateInputShootFormat(input))
    {
      //display message error
      std::cout << "\033[1;31mIncorrect entry, try again (e.g. B4 1 V).\033[0m\n\n";
      continue;
    }
    coordInput = getParams(input, REGEXSHOOTTILE);
    //validate is within limits
    //calculate index value ((row * length of grid's side) + col)    
    indVal = userInputToIndex(coordInput.row, coordInput.column, gridSize); 
    
    if(!(isManualTargetValid(indexVecPlayer, indVal) && validateBounds(coordInput.row, coordInput.column, gridSize)))
    {
      //display message error
      std::cout << "\033[1;31mTile already shot or target out of boundaries, try again.\033[0m\n\n";
      continue;
    }
    
    playerShoot(indexVecPlayer, indVal, gridSize, coordInput, grid, false);  
    //keep track of bombed tiles         
    bombedTilesGrid.push_back(indVal); 
    //user ends turn or quits game
    input = menuTurn();
    if (input == "0") {
      isNotQuit = false;            
    }                         
    break; 
  } 
}

void playerShootTurn(Grid& grid, std::vector<int> indexVecPlayer, std::vector<int> bombedTilesGrid, char playerLabel, udtCoordInput coordInput, int indVal, int gridSize, bool& isNotQuit) 
{
  std::string input;
  //display oponent's board
  std::cout << YELLOW << "\nPlayer" << playerLabel << " \'s turn\n" << ENDCOLOUR;
  grid.renderGrid();

  //ask shoot method. Manual/auto-fired
  input = menuShoot();
  if (input == "1") {      
    manualShoot(coordInput, indVal, gridSize, indexVecPlayer, bombedTilesGrid, isNotQuit, grid); 
  }
  //autofire
  else 
  {        
    //add time delay
    //add a time delay to improve game's pace.
    usleep(2000000);
    
    autoFire(indexVecPlayer, gridSize, coordInput, grid, bombedTilesGrid, isNotQuit);
  }
}