#pragma once

#include <regex>
#include <vector>
#include <map>
#include <set>

#include "states/BaseState.h"
#include "constants.h"
#include "Grid.h"
#include "Tile.h"

typedef std::map<std::string, BaseState*> MAP;

std::smatch extractSubStr(std::string input, std::string regPatt);

//Parsing player input
udtCoordInput getParams(std::string input, std::string regPatt);

std::string userInput(std::string msg); 

int calcShipLength(int shipType);

int letterToInt(char letter);

char intToLetter(int x);

std::set<int> createSet(int size);

int randomVal( int min, int max);

char orientationIntToChar(int orientation);

int availableTiles(char orientation, int randomNum, int gridSize, std::set<int>& index, int shipLen);

void removeValueSet(char orientation, int randomNum, int gridSize, std::set<int>& index, int shipLen);

void removeTarjetVector(int randomNum, std::vector<int>& indexVec);

udtCoordInput indexToXY(int index, int gridSize);

std::string getStringForEnum( int enum_val );

bool continueResetQuit(Grid& grid);

std::vector<int> vectorResourse(int size); 

int userInputToIndex(char row, int column, int gridSize);
