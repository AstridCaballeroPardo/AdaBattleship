# Testing

## Testing classes Grid, Ship, Tile and Fleet
### Testing Tile class
```
Tile tileA;
std::cout << tileA.getX() << '\n';
std::cout << tileA.getY() << '\n';
tileA.setX('B');
std::cout << tileA.getX() << '\n';
std::cout << tileA.getTileState() << '\n';
```
### Testing Ship class
```
Ship ship1;  
std::cout << ship1.getShipId() << '\n';
Ship ship2;  
std::cout << ship2.getShipId() << '\n';
std::cout << ship2.getOrientation() << '\n';

ship2.setShip((int)shipType::carrier, (int)shipOrientation::vertical);
std::cout << '\n' << ship2.getShipType() << '\n';
std::cout << ship2.getShipLen() << '\n';
std::cout << ship2.getOrientation() << '\n';
```
### Testing extraction of parameters from player input to create ship
```
std::string input = "a12 0 v";
std::string subStr1;
std::string subStr2;
std::regex regexInput(REGEXPLACESHIP); 
std::smatch subStrMatch;

std::regex_search(input, subStrMatch, regexInput);
subStr1 = subStrMatch[1].str();
subStr2 = subStrMatch[2].str();

std::cout << subStr1 << '\n';
std::cout << subStr2 << '\n';
```

### Testing fleet class
```
Fleet fleetPlayer = grid.getFleet();
std::vector<Ship>& ships = fleetPlayer.getFleetVector();
std::cout << "Grid Id: \n";
std::cout << grid.getGridId() << '\n';

std::cout << "fleetPlayer: \n";
std::cout << "Fleet id: " << fleetPlayer.getGridId() << '\n';
std::cout << "Fleet size: " << fleetPlayer.getSize() << '\n';

for (int i = 0; i < fleetPlayer.getSize(); i++) {  
  std::cout << ships[i].getShipType() << '\n'; 
}
```
*creating first ship*
```
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
```
*creating second ship*
```
input = "e6 2 v";
coordInput = getParams(input, grid);

grid.updateGrid(coordInput.row, coordInput.column, coordInput.shipType, coordInput.orientation); 

grid.renderGrid();

fleetPlayer = grid.getFleet();
ships = fleetPlayer.getFleetVector();

for (int i = 0; i < fleetPlayer.getSize(); i++) {  
  std::cout << ships[i].getShipType() << '\n'; 
  std::cout << ships[i].getShipId() << '\n';
}
```

### test write and read from two players
```
int shipIndex = 0;
int shipLen = 0;
char shipOrientation = ' ';
```

*check player info*
```
std::cout << "\033[1;32mPlayer's Fleet:\033[0m\n";
std::cout << "grid's id: " << gridPlayer.getGridId() << '\n';
Fleet gridFleetPlayer = gridPlayer.getFleet(); 
std::vector<Ship>& shipsPlayer = gridFleetPlayer.getFleetVector();
for (int i = 0, count = 0; i < shipsPlayer.size(); i++) {  
    std::cout << '\n';    
      //find ship
      shipIndex = shipsPlayer[i].getShipIndex();
      udtCoordInput xy = indexToXY(shipIndex, gridPlayer.getSize());
      int x = letterToInt(xy.row);
      int y = xy.column;
      shipLen = shipsPlayer[i].getShipLen();     
      shipOrientation = shipsPlayer[i].getOrientation(); 

      std::cout << "Ship orientation: " <<  shipOrientation << '\n'; 
      std::cout << "Ship length: " <<  shipLen << '\n'; 
      std::cout << "Ship type: " <<  shipsPlayer[i].getShipType() << '\n'; 
      
      //access fleet's tiles
      for (int n = 0; n < shipLen; n++) {
        
        if (shipOrientation == 'H') {
        
        Tile& newTile = gridPlayer.getGrid()[x][y + n]; 
        std::cout << "row: " << newTile.getX() << '\n';
        std::cout << "column: " << newTile.getY() << '\n';
        std::cout << "ship Id: " << newTile.getShipId() << '\n';
        std::cout << "ship TileState: " << newTile.getTileState() << '\n';
        std::cout << "ship symbol: " << newTile.getIcon() << '\n';            
        } else if (shipOrientation == 'V') {

        Tile& newTile = gridPlayer.getGrid()[x + n][y]; 

        std::cout << "row: " << newTile.getX() << '\n';
        std::cout << "column: " << newTile.getY() << '\n';
        std::cout << "ship Id: " << newTile.getShipId() << '\n';
        std::cout << "ship TileState: " << newTile.getTileState() << '\n';
        std::cout << "ship symbol: " << newTile.getIcon() << '\n';
      }
  }
}

std::cout << '\n';
```
*check computer info*
``` 
std::cout << "\033[1;32mComputer's Fleet:\033[0m\n";
std::cout << "grid's id: " << gridComputer.getGridId() << '\n';
Fleet gridFleetComputer = gridComputer.getFleet(); 
std::vector<Ship>& shipsComputer = gridFleetComputer.getFleetVector();
for (int i = 0, count = 0; i < shipsPlayer.size(); i++) {  
    std::cout << '\n';    
      //find ship
      shipIndex = shipsComputer[i].getShipIndex();
      udtCoordInput xy = indexToXY(shipIndex, gridComputer.getSize());
      int x = letterToInt(xy.row);
      int y = xy.column;
      shipLen = shipsComputer[i].getShipLen();     
      shipOrientation = shipsComputer[i].getOrientation(); 

      std::cout << "Ship orientation: " <<  shipOrientation << '\n'; 
      std::cout << "Ship length: " <<  shipLen << '\n'; 
      std::cout << "Ship type: " <<  shipsComputer[i].getShipType() << '\n'; 
```
*access fleet's tiles* 
```
      for (int n = 0; n < shipLen; n++) {
        
        if (shipOrientation == 'H') {
        
        Tile& newTile = gridComputer.getGrid()[x][y + n]; 
        std::cout << "row: " << newTile.getX() << '\n';
        std::cout << "column: " << newTile.getY() << '\n';
        std::cout << "ship Id: " << newTile.getShipId() << '\n';
        std::cout << "ship TileState: " << newTile.getTileState() << '\n';
        std::cout << "ship symbol: " << newTile.getIcon() << '\n';            
        } else if (shipOrientation == 'V') {

        Tile& newTile = gridComputer.getGrid()[x + n][y]; 

        std::cout << "row: " << newTile.getX() << '\n';
        std::cout << "column: " << newTile.getY() << '\n';
        std::cout << "ship Id: " << newTile.getShipId() << '\n';
        std::cout << "ship TileState: " << newTile.getTileState() << '\n';
        std::cout << "ship symbol: " << newTile.getIcon() << '\n';
      }
  }
} 
```