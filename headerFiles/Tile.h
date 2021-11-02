#pragma once

#include <string>
#include <vector>
#include <memory>

class Tile{
  private:
    char x_;
    int y_;
    int tileState_;
    int shipId_;
    char icon_;

  public:
    //constructor
    Tile(); 

    //member methods
    void setX(char x);
    void setY(int y);
    void setTileState(int tileState);
    void setShipId(int shipId);
    void setIcon(char icon);

    //inline implementation to have access to the private attributes
    char getX() const {return x_;}
    int getY() const {return y_;}
    int getTileState() const {return tileState_;}
    int getShipId() const {return shipId_;}
    char getIcon() const {return icon_;}      
  
};