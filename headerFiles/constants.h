#pragma once

#define GRID_SIZE 5
#define CAPITAL_LETTER 65
#define TILE_WIDTH 5

enum class TileState 
{
  emptyTile,
  shipTile,
  bombedTile
};