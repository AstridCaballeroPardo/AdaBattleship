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
bool validateCoordLimits(udtCoordInput coord, int gridSize){  
  if ((coord.column >= 1 && coord.column <= gridSize) && (coord.row >= CAPITAL_LETTER && coord.row < CAPITAL_LETTER + gridSize)) {
    //check if last tile for requested ship is within limits  
    int len = calcShipLength(coord.shipType) - 1;  
    //horizontally
    if (coord.orientation == 'H'){
      if (coord.column + len <= gridSize  ) {
        return true;
      }
    }
    //vertically
    else if (coord.orientation == 'V' ) {
      if (coord.row + len < CAPITAL_LETTER + gridSize) {
        return true;
      }
    }    
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
udtCoordInput getParams(std::string input){
  std::smatch matchResult;
  std::string row;
  std::string orientation;  
  udtCoordInput coord;
  coord.row = ' ';
  coord.column = -1;  
  coord.shipType = -1;
  coord.orientation = ' ';
  
  //check format of input          
    // if (validateInputFormat(input)){
      //parse the input
      matchResult = extractSubStr(input, REGEXPLACESHIP);
      
      //extract row from string      
      row = matchResult[1];            
      coord.row  = toupper(*row.c_str());//dereferencing the char*
     
      //extract column from string and make it zero based
      coord.column = std::stoi(matchResult[2]) - 1;

      //extract shipType     
      coord.shipType = std::stoi(matchResult[3]);

      //extract orientation     
      orientation = matchResult[4];
      coord.orientation = toupper(*orientation.c_str());//dereferencing the char*          
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

std::set<int> createSet(int size){
   std::set<int> mySet;
  
  for (int i = 0; i < size; i++) {
    mySet.insert(i);
  }  
  return mySet;
}

int randomVal(int min, int max) {
  std::random_device ramdomDev;
   std::mt19937 rng(ramdomDev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);

    return dist(rng);
}

char orientationIntToChar(int orientation) {
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

int availableTiles(char orientation, int randomNum, int gridSize, std::set<int>& index, int len) {
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

void removeValueSet(char orientation, int randomNum, int gridSize, std::set<int>& index, int len) {
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

udtCoordInput indexToXY(int index, int gridSize) {
  udtCoordInput xy;
  xy.row = intToLetter((index / gridSize));
  xy.column = (index % gridSize);
  return xy;
}