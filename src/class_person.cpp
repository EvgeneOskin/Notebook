#include "def_note.h"
using namespace std;

Person::Person ()
{
  ID = 0;
  Age = 0;
}

Person::~Person()
{
  //  cout << "i am destructor!\n" << ID << '\n';
}

unsigned short int Person::add_Age(int new_Age)
{
  unsigned short int goodness_INDEX = 1;
  Age = new_Age;
  return goodness_INDEX;
}

unsigned short int Person::add_Name(string &new_Name)
{
  unsigned short int goodness_INDEX = 1;
  if (new_Name.size() != 0)
    Name = new_Name;
  return goodness_INDEX;
}

unsigned short int Person::add_Second_Name(string &new_Second_Name)
{
  unsigned short int goodness_INDEX = 1;
  if (new_Second_Name.size() != 0)
    Second_Name = new_Second_Name;
  return goodness_INDEX;
}

unsigned short int Person::add_Phone(string &new_Phone)
{
  unsigned short int goodness_INDEX = 1;
  if (new_Phone.size() != 0)
    Phone = new_Phone;
  return goodness_INDEX;
}

unsigned short int Person::add_Notes(string &new_Notes)
{
  unsigned short int goodness_INDEX = 1;
  if (new_Notes.size() != 0)
    Notes = new_Notes;
  return goodness_INDEX;
}

