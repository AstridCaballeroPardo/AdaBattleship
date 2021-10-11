class VectorResource
{
  private:
    std::vector<std::vector<int>> grid;
  public:
  VectorResource();
  ~VectorResource(void);
  std::vector<std::vector<int>> getGrid() const {return grid;}
}; 