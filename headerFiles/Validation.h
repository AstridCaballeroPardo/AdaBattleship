#pragma once

#include <regex>

#include "constants.h"


bool validateInputFormat(std::string str);

bool validateInputShootFormat(std::string str);

bool validateInputMenu(std::string str, std::string regPatt);

bool validateBounds(char row, int column, int gridSize);

bool isManualTargetValid(std::vector<int> vectorResourse, int val);