#pragma once

#include <vector>
#include <set>

#include "Grid.h"

void manuallySetFleet(Grid& grid);
void getUnplacedShips(Grid& grid, int shipCount, std::vector<int>& unplacedShipsVect, int gridSize, std::set<int>& indexSet);
void automaticallySetFleet(Grid& grid);
void placing(Grid& grid);
void setPlayersType(Grid& gridPlayer1, Grid& gridPlayer2, std::string type);
void playerTurnLoop(Grid& grid, bool& isNotQuit, char playerLabel);