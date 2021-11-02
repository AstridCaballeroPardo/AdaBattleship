#pragma once

#define GRID_SIZE 10
#define CAPITAL_LETTER 65
#define TILE_WIDTH 5
#define TILE_PADDING 2
#define FLEET_SIZE 5
#define REGEXPLACESHIP R"((^[a-zA-Z])[^\S]?([0-9]{1,2})[^\S]([1-5])[^\S]?([hHvV])$)" // regex using subgroups for parsing and validation
#define REGEXSHOOTTILE R"((^[a-zA-Z])[^\S]?([0-9]{1,2})$)"
#define MENUENTRY R"(^[01]$)"
#define MENURESET R"(^[1230]$)"
#define MENUTRANSTOPLAY R"(^[10]$)"
#define MENUTURN R"(^[10]$)"
#define MENUSETMODE R"(^[12]$)"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define LIGHTBLUE "\033[2;94m"
#define YELLOW "\033[1;33m"
#define BLUEBACK "\033[1;34;104m"
#define ENDCOLOUR "\033[0m"


enum class tileState 
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