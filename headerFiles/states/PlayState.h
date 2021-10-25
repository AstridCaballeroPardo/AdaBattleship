#pragma once

class PlayState: public BaseState {
  public:
    //Constructor
    PlayState();
    //Destructor
    ~PlayState();

    //member methods
    void enter();
    void exit();
    void update();
    void render();
};