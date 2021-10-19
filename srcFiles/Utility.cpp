#include <iostream>
#include <memory>
#include <regex>
#include <cctype>

#include "../headerFiles/constants.h"
#include "../headerFiles/Grid.h"

//validate the player input has follows the expected pattern
bool validateInputFormat(std::string str){
   std::regex regexPattern(REGEXPLACESHIP); //starts with a letter, has only one letter, after the letter it might have one space, after a space (if exists) must have a number of max two digits (grid won't be bigger than 25x25 this is a constraint in order to not exceed the row letters and avoid to go into double letters (i.e. AA, AB, etc))   
    std::smatch match;  
    if (std::regex_search(str, match, regexPattern)){
      return true;
    }
    return false;
}

//validate player's target is within the grid boundaries
bool validateCoordLimits(udtCoordInput coord){
  if (coord.column >= 1 && coord.column <= GRID_SIZE && coord.row >= CAPITAL_LETTER && coord.row < CAPITAL_LETTER + GRID_SIZE) {
    return true;
  }
  else {return false;}
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
udtCoordInput getParams(std::string input, Grid grid){
  std::smatch matchResult;
  std::string row;
  std::string orientation;
  char orient;
  udtCoordInput coord;
  coord.row = ' ';
  coord.column = -1;  
  coord.shipType = -1;
  coord.orientation = 0;
  
  //check format of input          
    // if (validateInputFormat(input)){
      //parse the input
      matchResult = extractSubStr(input, REGEXPLACESHIP);
      
      //extract row from string      
      row = matchResult[1];            
      coord.row  = toupper(*row.c_str());//dereferencing the char*
     
      //extract column from string
      coord.column = std::stoi(matchResult[2]);

      //extract shipType     
      coord.shipType = std::stoi(matchResult[3]);

      //extract orientation     
      orientation = matchResult[4];
      orient = toupper(*orientation.c_str());//dereferencing the char*

      switch(orient) {
        case 'V': 
          coord.orientation = 1;
          break;
        case 'H':
          coord.orientation = 2;
          break;               
      }           
    // }      
  return coord;
}

std::string userInput(std::string msg) {
  std::string reply = "";  
  std::cout << msg;    
  std::getline(std::cin, reply);  
  return reply;
}

//calculate the len a ship will be
 int calcShipLength(int shipType){
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

int letterToInt(char letter){
   return letter - CAPITAL_LETTER ;
}
char intToLetter(int x){
   return x + CAPITAL_LETTER ;
}

bool isShipInFleet(std::vector<Ship>& ships, int shipType){
    for (int i = 0; i < ships.size(); i++) {
      if (ships[i].getShipType() == shipType) {        
        return true;
      }
    }
    return false;
}

bool areTilesAvailable(int len, int orientation, int x, int y, int tileState, std::vector<std::vector<Tile>>& grid){
  int countAvailableTiles = 0;
  for (int n = 0; n < len; n++) {
      //check horizontally to the right 
      if (orientation == 2) {      
        //check if tile is empty
        if (grid[x][(y - 1) + n].getTileState() == tileState) {
          countAvailableTiles++;
        }    
      }
      //check vertically to the bottom
      else {
        if (grid[x + n][y - 1].getTileState() == tileState) {
          countAvailableTiles++;
        }  
      }
    }
  if (countAvailableTiles == len) {
    return true;
  }
  return false;
}