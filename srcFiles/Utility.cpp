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
std::string extractSubStr(std::string input, std::string regPatt, int group = 0){
  std::string subStr;
  std::regex regexLetter(regPatt); 
  std::smatch subStrMatch;
  std::regex_search(input, subStrMatch, regexLetter);
  subStr = subStrMatch[group];

  return subStr;
}

//get the coordinates in the expected format and store it as a struct that holds a char and an integer
udtCoordInput getParams(std::string input, Grid grid){
  std::string row;
  std::string orientation;
  char orient;
  udtCoordInput coord;
  coord.row = ' ';
  coord.column = -1;  
  coord.shipType = -1;
  coord.orientation = 0;
  
  //check format of input          
    if (validateInputFormat(input)){
      //extract row from string      
      row = extractSubStr(input, REGEXPLACESHIP, 1);      
      coord.row  = toupper(*row.c_str());//dereferencing the char*
     
      //extract column from string      
      coord.column = std::stoi(extractSubStr(input, REGEXPLACESHIP, 2));

      //extract shipType
      coord.shipType = std::stoi(extractSubStr(input, REGEXPLACESHIP, 3));

      //extract orientation
      orientation = extractSubStr(input, REGEXPLACESHIP, 4);
      orient = toupper(*orientation.c_str());//dereferencing the char*

      switch(orient) {
        case 'V': 
          coord.orientation = 1;
          break;
        case 'H':
          coord.orientation = 2;
          break;               
      }           
    }      
  return coord;
}