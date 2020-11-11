#include <stdlib.h>
#include <iostream>
using namespace std;

// C-style structure
struct people{
  int tag;
  int age;
};
typedef struct people PeopleStruct;
typedef PeopleStruct *People;
// related functions 
People initPeople(int tag, int age);
void *killPeople(People victim);

// Cpp-Style Class
class Human{
  public:
    Human()
    {
      age = 10;
      sex = 0;
    }

    int getAge(){
      return age;
    }

    int getSex(){
      return sex;
    }

  private:
    int age;
    int sex;
};


int main()
{
  People newbie_A;
  newbie_A = initPeople(22, 99);
  killPeople(newbie_A);

  Human newbie_B;
  cout << newbie_B.getAge();

  return 0;
}

People initPeople(int tag, int age)
{
  People newbie;
  newbie = NULL;
  newbie = (People)malloc(sizeof(PeopleStruct));
  if (newbie != NULL)
    return NULL;

  return newbie;
}

void *killPeople(People victim)
{
  free(victim);
  victim = NULL;
  return NULL;
}
