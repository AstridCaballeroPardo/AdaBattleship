#pragma once


bool validateCoordFormat(std::string str);

bool validateCoordLimits(udtCoord coord);

udtCoord getXY(std::string input, Grid grid);