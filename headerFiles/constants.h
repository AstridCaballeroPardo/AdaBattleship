#pragma once



#define GRID_SIZE 10
#define CAPITAL_LETTER 65
#define TILE_WIDTH 5
#define TILE_PADDING 2
#define FLEET_SIZE 5
#define REGEXPLACESHIP R"((^[a-zA-Z])[^\S]?([0-9]{1,2})[^\S]([1-5])[^\S]?([hHvV])$)" // regex using subgroups for parsing and validation



enum class TileState 
{
  emptyTile,
  shipTile,
  bombedTile
};

enum class shipType 
{
  none,
  carrier,
  battleship,
  destroyer,
  submarine,
  patrolBoat
};

enum class shipOrientation
{
  none,
  vertical,
  horizontal
};

//create a struct to hold the extracted coordinates, ship type and orientation from the player's input
struct udtCoordInput{
  char row;
  int column;
  int shipType;
  char orientation;
};