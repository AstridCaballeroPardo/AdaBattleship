#pragma once

class GameOverState: public BaseState {
  public:
    //Constructor
    GameOverState();
    //Destructor
    ~GameOverState();

    //member methods
    void enter();
    void exit();
    void update();
    void render();
};