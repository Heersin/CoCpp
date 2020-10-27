class Human
{
  public:
    int caller() { return this->callee(); }
  private:
    int callee() { return 1; }
};


int main()
{
  Human newbie;
  int result;
  
  result = newbie.caller();
  return result;
}
