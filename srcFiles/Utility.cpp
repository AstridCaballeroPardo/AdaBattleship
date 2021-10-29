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

void playerShoot(std::set<int>& indexSetPlayer, int valIndex, int gridSize, udtCoordInput coordInput, bool& keepPlaying, Grid* gridPlayer)
{
  int shipTargetId;
  int tileTargetState;
  int x;
  //check random index is in set(find is O(log n))
  // if (indexSetPlayer.find(valIndex) != indexSetPlayer.end())
  // {
    if (gridPlayer->getPlayerType() == "human") {
      x = (valIndex / gridSize);            
      coordInput.column = (valIndex % gridSize);
    } 
    else if (gridPlayer->getPlayerType() == "computer")
    {
      x = letterToInt(coordInput.row);
    }
    

    //go to targeted tile
    std::vector<std::vector<Tile>>& grid = gridPlayer->getGrid();
    Tile& tileTarget = grid[x][coordInput.column];
    tileTargetState = tileTarget.getTileState();

    if (tileTargetState == 1) 
    {
      //Update tile. change tileState and icon              
      tileTarget.setTileState((int)tileState::bombedTile);
      tileTarget.setIcon('X');

      //identify shipId from tile
      shipTargetId = grid[x][coordInput.column].getShipId();
      
      //find ship in fleet
      std::vector<Ship>& ships = gridPlayer->getFleet().getFleetVector();              
      Ship& shipTarget = gridPlayer->getFleet().getShip(ships, shipTargetId);
      if (shipTarget.getShipId() == shipTargetId)
      {
        //reduce length
        shipTarget.reduceShipLen();

        //update fleet if ship is sunk
        if (shipTarget.getShipLen() == 0)
        {
          shipTarget.setIsSunk(true);
          std::cout << "\033[1;32mShip is sunk!\033[0m\n";

          Fleet& fleet = gridPlayer->getFleet();
          fleet.reduceFleetSize();
          
          if (fleet.getSize() == 0) 
          {
            std::cout << "\033[1;32mFleet is sunk!\033[0m\n";
            keepPlaying = false;
          } 
        }
      }
    } 
    else if (tileTargetState == 0) 
    {
      //Update tile. change tileState and icon
      tileTarget.setTileState((int)tileState::bombedTile);              
    }

    //if human it is allowed to shoot an already shooted tile, human wastes her/his turn    
    if (gridPlayer->getPlayerType() == "computer")
    {
      //remove tile's index from set so computer won't select it again
      removeTarjetSet(valIndex, indexSetPlayer);
    }

    //end of players's turn
    //display player's grid
    gridPlayer->renderGrid();                
  // }
}

std::string menuContinue()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENURESET))
  {
    std::string msg = "Select next step:\n1.continue\n2.reset\n3.quit\n";
    input = userInput(msg);
  }
  
  return input;
}

std::string menuTransToPlay()
{
  std::string input = " ";
  while(!validateInputMenu(input, MENUTRANSTOPLAY))
  {
  std::string msg = "Select next step:\n1.continue\n2.quit\n";
  input = userInput(msg);
  }
  return input;
}

void resetTiles(int len, std::vector<std::vector<Tile>>& grid,char orientation, int x, int y, char row, int column, int tileState, char icon, int shipId) 
{
  for (int n = 0; n < len; n++) 
        {
          //reset horizontally to the right 
          if (orientation == 'H') 
          {
            //reset tile
            grid[x][y + n].setX(row) ; 
            //to set y, add 1 to 'y' because y has a zero based value (0 to (GRID_SIZE - 1)) but it needs to be one based value (1 to GRID_SIZE)
            grid[x][y + n].setY(column);
            grid[x][y + n].setTileState(tileState);
            grid[x][y + n].setIcon(icon);
            grid[x][y + n].setShipId(shipId);
          }  
          //reset vertically to the bottom
          else if(orientation == 'V')
          {
            //reset tile
            grid[x + n][y].setX(row) ;  
            //to set y, add 1 to 'y' because y has a zero based value (0 to (GRID_SIZE - 1)) but it needs to be one based value (1 to GRID_SIZE)     
            grid[x + n][y].setY(column);
            grid[x + n][y].setTileState(tileState);
            grid[x + n][y].setIcon(icon);
            grid[x + n][y].setShipId(shipId);
          }
        } 
}

bool isHuman(Grid* gridPlayer){
  if (gridPlayer->getPlayerType() == "computer") {
    return false;
  }
  return true;
}