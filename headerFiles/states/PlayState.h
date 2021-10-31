#pragma once

class PlayState: public BaseState {
  // private:
    // std::vector<int> bombedTilesGrid1;
    // std::vector<int> bombedTilesGrid2;

  public:
    //Constructor
    PlayState();
    //Destructor
    ~PlayState();

    //member methods
    void enter();
    void exit(std::vector<int>& bombedTilesGrid1, std::vector<int>& bombedTilesGrid2);
    void update();
    void render();  
};