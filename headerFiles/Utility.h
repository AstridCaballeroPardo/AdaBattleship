#pragma once


bool validateInputFormat(std::string str);

bool validateCoordLimits(udtCoordInput coord);

std::string extractSubStr(std::string input, std::string regPatt, int group);

udtCoordInput getParams(std::string input, Grid grid);
