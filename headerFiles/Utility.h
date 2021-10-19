#pragma once

#include <regex>

#include "Grid.h"

bool validateInputFormat(std::string str);

bool validateCoordLimits(udtCoordInput coord, int gridSize);

std::smatch extractSubStr(std::string input, std::string regPatt);

//Parsing player input
udtCoordInput getParams(std::string input, Grid grid);

std::string userInput(std::string msg); 

int calcShipLength(int shipType);

int letterToInt(char letter);

char intToLetter(int x);

bool isShipInFleet(std::vector<Ship>& ships, int shipType);

bool areTilesAvailable(int len, int orientation, int x, int y, int tileState, std::vector<std::vector<Tile>>& grid);