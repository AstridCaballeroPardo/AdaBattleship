#include <iostream>
#include <memory>
#include <regex>
#include <cctype>
#include <set>
#include <random>
#include <math.h> 

#include "../headerFiles/constants.h"
#include "../headerFiles/Grid.h"
#include "../headerFiles/Utility.h"
#include "../headerFiles/Menu.h"

//validate the player input has follows the expected pattern to place ships
bool validateInputFormat(std::string str)
{
   std::regex regexPattern(REGEXPLACESHIP); //starts with a letter, has only one letter, after the letter it might have one space, after a space (if exists) must have a number of max two digits (grid won't be bigger than 25x25 this is a constraint in order to not exceed the row letters and avoid to go into double letters (i.e. AA, AB, etc))   
    std::smatch match;  
    if (std::regex_search(str, match, regexPattern)){
      return true;
    }
    return false;
}

//validate the player input has follows the expected pattern to shoot
bool validateInputShootFormat(std::string str)
{
  std::regex regexPattern(REGEXSHOOTTILE); //starts with a letter, has only one letter, after the letter it might have one space, after a space (if exists) must have a number of max two digits (grid won't be bigger than 25x25 this is a constraint in order to not exceed the row letters and avoid to go into double letters (i.e. AA, AB, etc))   
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

bool isShipInFleet(std::vector<Ship>& ships, int shipType)
{
    for (int i = 0; i < ships.size(); i++) {
      if (ships[i].getShipType() == shipType) {        
        return true;
      }
    }
    return false;
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

void removeTarjetSet(int randomNum, std::set<int>& index)
{
  index.erase(randomNum);
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

void playerShoot(std::set<int>& indexSetPlayer, int valIndex, int gridSize, udtCoordInput coordInput, Grid& gridPlayer)
{
  int shipTargetId;
  int tileTargetState;
  int x;
  //check random index is in set(find is O(log n))
  // if (indexSetPlayer.find(valIndex) != indexSetPlayer.end())
  // {
    if (gridPlayer.getPlayerType() == "human") {
      x = (valIndex / gridSize);            
      coordInput.column = (valIndex % gridSize);
    } 
    else if (gridPlayer.getPlayerType() == "computer")
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
      // if (shipTarget.getShipId() == shipTargetId)
      // {
        //reduce length
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
      // }
    } 
    else if (tileTargetState == 0) 
    {
      //Update tile. change tileState and icon
      tileTarget.setTileState((int)tileState::bombedTile);              
    }

    //if human it is allowed to shoot an already shooted tile, human wastes her/his turn    
    if (gridPlayer.getPlayerType() == "computer")
    {
      //remove tile's index from set so computer won't select it again
      removeTarjetSet(valIndex, indexSetPlayer);
    }

    //end of players's turn
    //display player's grid
    gridPlayer.renderGrid(); 
}

void resetTiles(int len, std::vector<std::vector<Tile>>& grid,char orientation, int x, int y, std::shared_ptr<Tile> tmpTile) 
{
  for (int n = 0; n < len; n++) 
        {
          //reset horizontally to the right 
          if (orientation == 'H') 
          {
            //reset tile            
            grid[x][y + n].setX(tmpTile->getX()) ; 
            //to set y, add 1 to 'y' because y has a zero based value (0 to (GRID_SIZE - 1)) but it needs to be one based value (1 to GRID_SIZE)
            grid[x][y + n].setY(tmpTile->getY());
            grid[x][y + n].setTileState(tmpTile->getTileState());
            grid[x][y + n].setIcon(tmpTile->getIcon());
            grid[x][y + n].setShipId(tmpTile->getShipId());
          }  
          //reset vertically to the bottom
          else if(orientation == 'V')
          {
            //reset tile
            grid[x + n][y].setX(tmpTile->getX()) ;  
            //to set y, add 1 to 'y' because y has a zero based value (0 to (GRID_SIZE - 1)) but it needs to be one based value (1 to GRID_SIZE)     
            grid[x + n][y].setY(tmpTile->getY());
            grid[x + n][y].setTileState(tmpTile->getTileState());
            grid[x + n][y].setIcon(tmpTile->getIcon());
            grid[x + n][y].setShipId(tmpTile->getShipId());
          }
        } 
}

bool isFleetCompleted(Grid* grid){
  int count = 0;
  for (int i = 0; i < grid->getFleet().getSize(); i++) {
    if (grid->getFleet().getFleetVector()[i].getShipType() != 0) {
      count++;
    }
  }
  if (count == grid->getFleet().getSize()) {
    return true;
  }
  return false;
}

bool continueResetQuit(Grid* grid) {
 std::string input;
 input = menuContinue();
 if (input == "1")
 {
   return true;
 }
 else if (input == "2")
 {
   grid->getFleet().resetFleet(grid->getGrid());
   return true;
 }
 else
 {
   return false;
 }
}
 
void placing(Grid* grid)
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
 
void playerTurn(Grid* grid)
{
 //keep placing for player or quit?
 grid->renderGrid();
 placing(grid);
 grid->renderGrid();
}
 
void setPlayersType(Grid* gridPlayer1, Grid* gridPlayer2, std::string type) {
 if (type == "1") {
   gridPlayer1->setPlayerType("human");
   gridPlayer2->setPlayerType("computer");
 }
 else if (type == "2") {
   gridPlayer1->setPlayerType("human");
   gridPlayer2->setPlayerType("human");
 }
}

void playerTurnLoop(Grid* grid, bool& isNotQuit, char playerLabel) { 
 while(!isFleetCompleted(grid)) {
         
     std::cout << YELLOW << "\nPlayer" << playerLabel << " set your fleet: \n" << ENDCOLOUR;
    
     playerTurn(grid);
         
     isNotQuit = continueResetQuit(grid);
     if(!isNotQuit) {
       break;
     }
   }
}

void resetTile(Grid& grid, int x, int y, std::shared_ptr<Tile> tmpTile)
{
 grid.getGrid()[x][y].setTileState(tmpTile->getTileState());
}

void resetBombedTiles(Grid& grid, std::vector<int>& bombedTilesGrid)
{
 std::shared_ptr<Tile> tmpTile = std::make_shared<Tile>();
 for (int i = 0; i < bombedTilesGrid.size(); i++)
 {
   //find tile and reset
   //define len, orientation, x and y
   int x =(bombedTilesGrid[i] / grid.getSize());
   int y = (bombedTilesGrid[i] % grid.getSize());
   //only reset the bombed tiles that didn't belong to ships. There is another reset function that reset the ships wheter they were bombed or not.
   if (grid.getGrid()[x][y].getIcon() == '~' && grid.getGrid()[x][y].getTileState() == 2)
   {
     resetTile(grid, x, y, tmpTile);
   }
 }
}