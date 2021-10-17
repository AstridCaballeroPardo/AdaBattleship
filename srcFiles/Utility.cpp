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