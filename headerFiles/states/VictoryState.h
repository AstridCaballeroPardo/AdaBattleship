#pragma once

class VictoryState: public BaseState {
  public:
    //Constructor
    VictoryState();
    //Destructor
    ~VictoryState();

    //member methods
    void enter(int params);
    void exit();
    void update();
    void render();
};