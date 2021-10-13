#include <iostream>
#include <memory>
#include <regex>
#include <cctype>

#include "../headerFiles/constants.h"
#include "../headerFiles/Grid.h"

//validate the player input has follows the expected pattern
bool validateCoordFormat(std::string str){
   std::regex regexPattern(R"(^[a-zA-Z][^\S]?[0-9]{1,2}+$)"); //starts with a letter, has only one letter, after the letter it might have one space, after a space (if exists) must have a number of max two digits (grid won't be bigger than 25x25 this is a constraint in order to not exceed the row letters and avoid to go into double letters (i.e. AA, AB, etc))   
    std::smatch match;  
    if (std::regex_search(str, match, regexPattern)){
      return true;
    }
    return false;
}

//validate player's target is within the grid boundaries
bool validateCoordLimits(udtCoord coord){
  if (coord.column >= 1 && coord.column <= GRID_SIZE && coord.row >= CAPITAL_LETTER && coord.row < CAPITAL_LETTER + GRID_SIZE) {
    return true;
  }
  else {return false;}
}


//extract substrings
std::string extractSubStr(std::string input, std::string regPatt){
  std::string subStr;
  std::regex regexLetter(regPatt); 
  std::smatch subStrMatch;
  std::regex_search(input, subStrMatch, regexLetter);
  subStr = subStrMatch[0];

  return subStr;
}

//get the coordinates in the expected format and store it as a struct that holds a char and an integer
udtCoord getXY(std::string input, Grid grid){
  std::string row;
  udtCoord coord;
  coord.row = ' ';
  coord.column = -1;  
  
  //check format of input          
    if (validateCoordFormat(input)){
      //extract row from string      
      row = extractSubStr(input, REGEXROW);      
      coord.row  = toupper(*row.c_str());//dereferencing the char*
     
      //extract column from string      
      coord.column = std::stoi(extractSubStr(input, REGEXCOL));
    }      
  return coord;
}