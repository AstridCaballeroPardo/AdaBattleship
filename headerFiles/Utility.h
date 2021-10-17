bool validateInputFormat(std::string str);

bool validateCoordLimits(udtCoordInput coord);

std::string extractSubStr(std::string input, std::string regPatt);

//Parsing player input
udtCoordInput getParams(std::string input, Grid grid);

std::string userInput(std::string msg); 