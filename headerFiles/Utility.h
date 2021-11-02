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

int availableTiles(char orientation, int randomNum, int gridSize, std::set<int>& index, int len);

void removeValueSet(char orientation, int randomNum, int gridSize, std::set<int>& index, int len);

void removeTarjetVector(int randomNum, std::vector<int>& indexVec);

udtCoordInput indexToXY(int index, int gridSize);

std::string getStringForEnum( int enum_val );

// void playerShoot(std::vector<int>& indexVectPlayer, int valIndex, int gridSize, udtCoordInput coordInput, Grid& gridPlayer, bool isAutofired);

bool continueResetQuit(Grid& grid);

void placing(Grid& grid);

void playerTurn(Grid& grid);

void setPlayersType(Grid& gridPlayer1, Grid& gridPlayer2, std::string type);

void playerTurnLoop(Grid& grid, bool& isNotQuit, char playerLabel);

std::vector<int> vectorResourse(int size); 

// bool isManualTargetValid(std::vector<int> vectorResourse, int val);

int userInputToIndex(char row, int column, int gridSize);

// void autoFire(std::vector<int>& indexVecPlayer, int gridSize, udtCoordInput coordInput, Grid& grid, std::vector<int>& bombedTilesGrid, bool& isNotQuit); 

// void manualShoot(udtCoordInput coordInput, int indVal, int gridSize, std::vector<int>& indexVecPlayer, std::vector<int>& bombedTilesGrid, bool& isNotQuit, Grid& grid); 