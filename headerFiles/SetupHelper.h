#pragma once

#include <vector>
#include <set>

#include "Grid.h"

void setupPlacingShip(int shipLen, udtCoordInput& coordInput, int randomIndex, int gridSize, std::vector<int>& unplacedShipsVect, int& placedShip, Grid& grid, std::set<int>& indexSet);
void manuallySetFleet(Grid& grid, bool hide);
void getUnplacedShips(Grid& grid, int shipCount, std::vector<int>& unplacedShipsVect, int gridSize, std::set<int>& indexSet);
void automaticallySetFleet(Grid& grid);
void placing(Grid& grid, bool hide);
void setPlayersType(Grid& gridPlayer1, Grid& gridPlayer2, std::string type);
void playerTurnLoop(Grid& grid, bool& isNotQuit, char playerLabel, bool hide);
void playerTurn(Grid& grid, bool hide);