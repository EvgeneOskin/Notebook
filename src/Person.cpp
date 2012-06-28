#include "def.h"
#include "Person.h"
using namespace std;


Person::Person ()
  : ID(0), Age(0), Save_Flag(false), Database_Flag(false)
{
}

Person::~Person()
{
  //  cout << "i am destructor!\n" << ID << '\n';
}

unsigned short int Person::add_Age(int new_Age)
{
  if (new_Age < 0)
    return 0;

  Age = new_Age;
  if (Age > 100)
    cout << "\033[0,32mThis Person is very old...\033[0m\n";
  return 1;
}

unsigned short int Person::add_Name(const string &new_Name)
{
  if (new_Name.empty())
    return 0;
  
  Name = new_Name;
  return 1;
}

unsigned short int Person::add_Second_Name(const string &new_Second_Name)
{
  if (new_Second_Name.empty())
    return 0;
  
  Second_Name = new_Second_Name;
  return 1;
}

unsigned short int Person::add_Phone(const string &new_Phone)
{
  if(new_Phone.empty())
    return 0;

  unsigned int Phone_amount = 0;
  if (*new_Phone.begin() == '+')
    Phone_amount++;
  BOOST_FOREACH(char new_Phone_char, new_Phone)
    {
      switch (new_Phone_char)
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
    }
  if (*new_Phone.begin() == '-')
    Phone_amount--;
  
  if  (new_Phone.size() != Phone_amount)
    return 0;

  Phone = new_Phone;
  return 1;
}

unsigned short int Person::add_Notes(const string &new_Notes)
{
  if (new_Notes.empty())
    return 0;
  
  Notes = new_Notes;
  return 1;
}

