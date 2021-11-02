#include <iostream>
#include <memory>
#include <regex>
#include <cctype>
#include <vector>
#include <random>
#include <math.h> 

#include "../headerFiles/constants.h"
#include "../headerFiles/Grid.h"
#include "../headerFiles/Validation.h"
#include "../headerFiles/Utility.h"
#include "../headerFiles/Menu.h"


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

std::vector<int> vectorResourse(int size) {
  std::vector<int> vectorR;
  for (int i = 0; i < size; i++) {
    vectorR.push_back(i);
  }
  return vectorR;
}

int userInputToIndex(char row, int column, int gridSize) {
  return ((row - CAPITAL_LETTER)  * gridSize) + column;
}