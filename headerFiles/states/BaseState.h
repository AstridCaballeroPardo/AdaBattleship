#pragma once

#include <vector>

//abstract class that will be the base for the 'states' of the game. 'virtual' is what allows polymorphism
class BaseState {
  public:
    //Constructor
    BaseState();
    //Destructor
    virtual ~BaseState();

    //member methods
    virtual void enter();
    virtual void enter(int params);
    virtual void exit();
    virtual void exit(std::vector<int>& bombedTilesGrid1, std::vector<int>& bombedTilesGrid2);
    virtual void update();
    virtual void render();
};

