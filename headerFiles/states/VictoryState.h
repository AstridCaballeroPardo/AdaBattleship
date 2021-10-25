class VictoryState: public BaseState {
  public:
    //Constructor
    VictoryState();
    //Destructor
    ~VictoryState();

    //member methods
    void enter();
    void exit();
    void update();
    void render();
};