
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "../headerFiles/Tile.h"
#include "../headerFiles/constants.h"

//Implementing constructor
Tile::Tile():x_(' '),y_(-1),tileState_((int)tileState::emptyTile),shipId_(0), icon_('~'){}

//member methods
void Tile::setX(char x)
{
  x_ = x;
}
void Tile::setY(int y)
{
  y_ = y;
}
void Tile::setTileState(int tileState)
{
  tileState_ = tileState;
}
void Tile::setShipId(int shipId)
{
  shipId_ = shipId;
}
void Tile::setIcon(char icon)
{
  icon_ = icon;
}


