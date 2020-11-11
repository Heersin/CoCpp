#include <iostream>
using namespace std;

class Human
{
  public:
    int tag;
    int getAge() { return age; }
    Human()
    {
      tag = 0;
      age = 1;
    }

  private:
    int age;
};

int main()
{
  Human newbie;
  newbie.tag = 10;
  return newbie.getAge();
}
