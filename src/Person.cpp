#include "def.h"
#include "Person.h"
using namespace std;

Person::Person ()
{
  ID = 0;
  Age = 0;
  Save_Flag = false;
  Database_Flag = false;
}

Person::~Person()
{
  //  cout << "i am destructor!\n" << ID << '\n';
}

unsigned short int Person::add_Age(int new_Age)
{
  unsigned short int goodness_INDEX = 1;
  if (new_Age == 0)
    goodness_INDEX = 0;
  else
      if (new_Age < 0)
	goodness_INDEX = 2;
      else
	{
	  Age = new_Age;
	  if (Age > 100)
	    cout << "\033[0,32mThis Person is very old...\033[0m\n";
	}
  return goodness_INDEX;
}

unsigned short int Person::add_Name(string &new_Name)
{
  unsigned short int goodness_INDEX = 1;
  if (new_Name.size() != 0)
    Name = new_Name;
  else
    goodness_INDEX = 0;
  return goodness_INDEX;
}

unsigned short int Person::add_Second_Name(string &new_Second_Name)
{
  unsigned short int goodness_INDEX = 1;
  if (new_Second_Name.size() != 0)
    Second_Name = new_Second_Name;
  else
    goodness_INDEX = 0;
  return goodness_INDEX;
}

unsigned short int Person::add_Phone(string &new_Phone)
{
  unsigned short int goodness_INDEX = 1;
  unsigned int Phone_amount = 0;
  string::iterator Phone_iterator;
  if (*new_Phone.begin() == '+')
    Phone_amount++;
  for (Phone_iterator = new_Phone.begin(); Phone_iterator < new_Phone.end(); Phone_iterator++)
    switch (*Phone_iterator)
      {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
      case '-': Phone_amount++; break;
      }
  if (*new_Phone.begin() == '-')
    Phone_amount--;
  if ((new_Phone.size() != 0) && (new_Phone.size() == Phone_amount))
    Phone = new_Phone;
  else
    goodness_INDEX = 0;
  return goodness_INDEX;
}

unsigned short int Person::add_Notes(string &new_Notes)
{
  unsigned short int goodness_INDEX = 1;
  if (new_Notes.size() != 0)
    Notes = new_Notes;
  return goodness_INDEX;
}

