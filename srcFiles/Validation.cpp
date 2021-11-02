#include <regex>

#include "../headerFiles/constants.h"


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

bool validateBounds(char row, int column, int gridSize) {
  if ((row - CAPITAL_LETTER ) < gridSize && (column >= 0 && column < gridSize)) {
    return true;
  }
  return false;
}

bool isManualTargetValid(std::vector<int> vectorResourse, int val) {
  for (int i = 0; i < vectorResourse.size(); i++) {
    if (vectorResourse[i] == val) {
      return true;
    }
  }
  return false;
} 