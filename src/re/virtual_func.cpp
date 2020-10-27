#include <iostream>
using namespace std;

class Animal
{
  public:
    virtual int eat() {
      return 0x0;
    }
};


class Cat : public Animal
{
  public:
    int eat() {
      return 0xF;
    }
};

int magic(Animal *sth);

int main()
{
  // Animal animal is similar
  // use * to keep uni with magic()
  Animal *animal;
  Cat *cat;

  animal = new Animal;
  cat = new Cat;

  int animal_eat;
  int cat_eat;

  animal_eat = animal->eat();
  cat_eat = cat->eat();
  cout << "animal eat : " << animal_eat << endl;
  cout << "cat eat : " << cat_eat << endl;

  animal_eat = magic(animal);
  cat_eat = magic(cat);
  cout << "animal eat : " << animal_eat << endl;
  cout << "cat eat : " << cat_eat << endl;

  delete animal;
  delete cat;

  return 0;
}

int magic(Animal *sth)
{
  return sth->eat();
}
