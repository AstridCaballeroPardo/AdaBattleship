//constraints
grid will be a square
side of grid won't be longer than the number of letters in the alphabet (26x26)

//Testing
  //Testing Tile class
  /** Tile tileA;
  std::cout << tileA.getX() << '\n';
  std::cout << tileA.getY() << '\n';
  tileA.setX('B');
  std::cout << tileA.getX() << '\n';
  std::cout << tileA.getTileState() << '\n'; **/

  //Testing Ship class
  /** Ship ship1;  
  std::cout << ship1.getShipId() << '\n';
  Ship ship2;  
  std::cout << ship2.getShipId() << '\n';
  std::cout << ship2.getOrientation() << '\n';

  ship2.setShip((int)shipType::carrier, (int)shipOrientation::vertical);
  std::cout << '\n' << ship2.getShipType() << '\n';
  std::cout << ship2.getShipLen() << '\n';
  std::cout << ship2.getOrientation() << '\n';**/


  //Testing extraction of parameters from player input to create ship
  /** std::string input = "a12 0 v";
  std::string subStr1;
  std::string subStr2;
  std::regex regexInput(REGEXPLACESHIP); 
  std::smatch subStrMatch;

  std::regex_search(input, subStrMatch, regexInput);
  subStr1 = subStrMatch[1].str();
  subStr2 = subStrMatch[2].str();

  std::cout << subStr1 << '\n';
  std::cout << subStr2 << '\n';**/

  // Testing fleet class
/** Fleet fleetPlayer = grid.getFleet();
std::vector<Ship>& ships = fleetPlayer.getFleetVector();
std::cout << "Grid Id: \n";
std::cout << grid.getGridId() << '\n';

std::cout << "fleetPlayer: \n";
std::cout << "Fleet id: " << fleetPlayer.getGridId() << '\n';
std::cout << "Fleet size: " << fleetPlayer.getSize() << '\n';

for (int i = 0; i < fleetPlayer.getSize(); i++) {  
  std::cout << ships[i].getShipType() << '\n'; 
}

//creating first ship
input = "A1 1 H";
coordInput = getParams(input, grid);

grid.updateGrid(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation); 

grid.renderGrid();

fleetPlayer = grid.getFleet();
ships = fleetPlayer.getFleetVector();

for (int i = 0; i < fleetPlayer.getSize(); i++) {  
  std::cout << ships[i].getShipType() << '\n'; 
  std::cout << ships[i].getShipId() << '\n';
}

//creating second ship
input = "e6 2 v";
coordInput = getParams(input, grid);

grid.updateGrid(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation); 

grid.renderGrid();

fleetPlayer = grid.getFleet();
ships = fleetPlayer.getFleetVector();

for (int i = 0; i < fleetPlayer.getSize(); i++) {  
  std::cout << ships[i].getShipType() << '\n'; 
  std::cout << ships[i].getShipId() << '\n';
}**/