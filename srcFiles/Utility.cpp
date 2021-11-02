#include <iostream>
#include <memory>
#include <regex>
#include <cctype>
#include <vector>
#include <random>
#include <math.h> 

#include "../headerFiles/constants.h"
#include "../headerFiles/Grid.h"
#include "../headerFiles/Utility.h"
#include "../headerFiles/Menu.h"

//validate the player input has follows the expected pattern to place ships
bool validateInputFormat(std::string str)
{
   std::regex regexPattern(REGEXPLACESHIP); //starts with a letter, has only one letter, after the letter it might have one space, after a space (if exists) must have a number of max two digits 
    std::smatch match;  
    if (std::regex_search(str, match, regexPattern)){
      return true;
    }
    return false;
}

//validate the player input has follows the expected pattern to shoot
bool validateInputShootFormat(std::string str)
{
  std::regex regexPattern(REGEXSHOOTTILE); //starts with a letter, has only one letter, after the letter it might have one space, after a space (if exists) must have a number of max two digits 
      std::smatch match;  
      if (std::regex_search(str, match, regexPattern)){
        return true;
      }
      return false;
}

//validate the player menu input has follows the expected pattern
bool validateInputMenu(std::string str, std::string regPatt)
{
  std::regex regexPattern(regPatt); //only has one number 
      std::smatch match;  
      if (std::regex_search(str, match, regexPattern)){
        return true;
      }
      return false;
}

//extract substrings
std::smatch extractSubStr(std::string input, std::string regPatt){
  // std::string subStr;
  std::regex regexLetter(regPatt); 
  std::smatch subStrMatch;
  std::regex_search(input, subStrMatch, regexLetter);
  // subStr = subStrMatch[group];

  return subStrMatch;
}

//get the coordinates in the expected format and store it as a struct that holds a char and an integer
udtCoordInput getParams(std::string input, std::string regPatt)
{
  std::smatch matchResult;
  std::string row;
  std::string orientation;  
  udtCoordInput coord;
  coord.row = ' ';
  coord.column = -1;  
  coord.shipType = -1;
  coord.orientation = ' ';
   
  //parse the input
  matchResult = extractSubStr(input, regPatt);
  
  //extract row from string      
  row = matchResult[1];            
  coord.row  = toupper(*row.c_str());//dereferencing the char*
  
  //extract column from string and make it zero based
  coord.column = std::stoi(matchResult[2]) - 1;

  if(matchResult.size() > 3){
    //extract shipType     
    coord.shipType = std::stoi(matchResult[3]);

    //extract orientation     
    orientation = matchResult[4];
    coord.orientation = toupper(*orientation.c_str());//dereferencing the char* 
  }
               
  return coord;
}

std::string userInput(std::string msg) 
{
  std::string reply = "";  
  std::cout << msg;    
  std::getline(std::cin, reply);  
  return reply;
}

//calculate the len a ship will be
 int calcShipLength(int shipType)
 {
  int Len = 0;
  switch(shipType) {
    case 1: 
      Len = 5;
      break;
    case 2:
      Len = 4;
      break;
    case 3: 
      Len = 3;
      break;
    case 4:
      Len = 3;
      break;
    case 5:
      Len = 2;
      break;
    case 0:    
      break;
  }
  return Len;
}

int letterToInt(char letter)
{
   return letter - CAPITAL_LETTER ;
}
char intToLetter(int x)
{
   return x + CAPITAL_LETTER ;
}


std::set<int> createSet(int size)
{
   std::set<int> mySet;
  
  for (int i = 0; i < size; i++)
  {
    mySet.insert(i);
  }  
  return mySet;
}

int randomVal(int min, int max)
{
  std::random_device ramdomDev;
   std::mt19937 rng(ramdomDev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);

    return dist(rng);
}

char orientationIntToChar(int orientation)
{
  char cOrientation = ' ';
  switch(orientation) {
          case 1: 
            cOrientation = 'V';
            break;
          case 2:
            cOrientation = 'H';
            break;               
        }
        return cOrientation;
}

int availableTiles(char orientation, int randomNum, int gridSize, std::set<int>& index, int len) 
{
  int availableTiles = 0;

  if (orientation == 'V') {      
        for (int i = randomNum + gridSize, j = 1; j < len; i+=gridSize, j++) {        
          if (index.find(i) != index.end()) {
              availableTiles++;
          } else {
            break;
          }
        }
      } else {
        for (int i = randomNum + 1, j = 1; j < len; i++, j++) {  
          //calculate row values to make sure elements belong to the same row
          char xRandom = intToLetter((randomNum / gridSize));
          char xNext = intToLetter((i / gridSize));

          if (index.find(i) != index.end() && xRandom == xNext ) {
              availableTiles++;
          }
        }
      }  
  return availableTiles;
}

void removeValueSet(char orientation, int randomNum, int gridSize, std::set<int>& index, int len) 
{
  if (orientation == 'V') {      
            for (int i = randomNum, j = 0; j < len; i+=gridSize, j++) {       
              index.erase(i);
            }
          } else {
            for (int i = randomNum, j = 0; j < len; i++, j++) {        
            index.erase(i);
            }
          }
}

void removeTarjetVector(int randomNum, std::vector<int>& indexVec)
{
  indexVec.erase(std::remove(indexVec.begin(), indexVec.end(), randomNum), indexVec.end());
}

udtCoordInput indexToXY(int index, int gridSize) 
{
  udtCoordInput xy;
  xy.row = intToLetter((index / gridSize));
  xy.column = (index % gridSize);
  return xy;
}

std::string getStringForEnum(int enum_val)
{
  std::string tmp;
    switch(enum_val){
      case 1:
      tmp = "Carrier";
      break;
      case 2:
      tmp = "Battleship";
      break;
      case 3:
      tmp = "Destroyer";
      break;
      case 4:
      tmp = "Submarine";
      break;
      case 5:
      tmp = "Patrol Boat";
      break;
    }
    return tmp;
}

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


bool continueResetQuit(Grid& grid) {
 std::string input;
 input = menuContinue();
 if (input == "1")
 {
   return true;
 }
 else if (input == "2")
 {
   grid.resetFleet();
   return true;
 }
 else
 {
   return false;
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

std::vector<int> vectorResourse(int size) {
  std::vector<int> vectorR;
  for (int i = 0; i < size; i++) {
    vectorR.push_back(i);
  }
  return vectorR;
}

bool isManualTargetValid(std::vector<int> vectorResourse, int val) {
  for (int i = 0; i < vectorResourse.size(); i++) {
    if (vectorResourse[i] == val) {
      return true;
    }
  }
  return false;
} 

int userInputToIndex(char row, int column, int gridSize) {
  return ((row - CAPITAL_LETTER)  * gridSize) + column;
}

bool withinBounds(char row, int column, int gridSize) {
  if ((row - CAPITAL_LETTER ) < gridSize && column < gridSize) {
    return true;
  }
  return false;
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
    
    if(!(isManualTargetValid(indexVecPlayer, indVal) && withinBounds(coordInput.row, coordInput.column, gridSize)))
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