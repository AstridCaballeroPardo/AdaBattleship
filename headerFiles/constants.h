#pragma once

#define GRID_SIZE 5
#define CAPITAL_LETTER 65
#define TILE_WIDTH 5
#define TILE_PADDING 2
#define REGEXROW R"([a-zA-Z])"
#define REGEXCOL R"([0-9]{1,2}+)"


enum class TileState 
{
  emptyTile,
  shipTile,
  bombedTile
};

//create a struct to hold the extracted coordinates from the player's input
struct udtCoord{
  char row;
  int column;
};