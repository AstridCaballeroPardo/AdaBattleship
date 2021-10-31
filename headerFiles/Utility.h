#pragma once

#include <regex>
#include <set>
#include <map>

#include "states/BaseState.h"
#include "constants.h"
#include "Grid.h"
#include "Tile.h"

typedef std::map<std::string, BaseState*> MAP;

bool validateInputFormat(std::string str);

bool validateInputShootFormat(std::string str);

bool validateCoordLimits(udtCoordInput coord, int gridSize);

std::smatch extractSubStr(std::string input, std::string regPatt);

//Parsing player input
udtCoordInput getParams(std::string input, std::string regPatt);

std::string userInput(std::string msg); 

int calcShipLength(int shipType);

int letterToInt(char letter);

char intToLetter(int x);

bool isShipInFleet(std::vector<Ship>& ships, int shipType);

std::set<int> createSet(int size);

int randomVal( int min, int max);

char orientationIntToChar(int orientation);

int availableTiles(char orientation, int randomNum, int gridSize, std::set<int>& index, int len);

void removeValueSet(char orientation, int randomNum, int gridSize, std::set<int>& index, int len);

void removeTarjetSet(int randomNum, std::set<int>& index);

udtCoordInput indexToXY(int index, int gridSize);

std::string getStringForEnum( int enum_val );

void playerShoot(std::set<int>& indexSetPlayer, int valIndex, int gridSize, udtCoordInput coordInput, bool& keepPlaying, Grid* gridPlayer);

bool validateInputMenu(std::string str, std::string regPatt);

void resetTiles(int len, std::vector<std::vector<Tile>>& grid,char orientation, int x, int y, char row, int column, int tileState, char icon, int shipId);

bool isFleetCompleted(Grid* grid);

bool continueResetQuit(Grid* grid);

void placing(Grid* grid);

void playerTurn(Grid* grid);

void setPlayersType(Grid* gridPlayer1, Grid* gridPlayer2, std::string type);
