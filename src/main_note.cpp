#include "def_note.h"

using namespace std;

int main (int argc, char* argv[])
{
  unsigned short int Empty_INDEX = 0;
  string Input_Information;
  vector <Person*> listing;
  cout << "Hello, type some one-word command for me.\n";
  while ( Input_Information.compare("quit") != 0)
    {
      Empty_INDEX = 0;
      cout << "# ";
      
      cin >> Input_Information;
      if (Input_Information.compare("add") == 0)
	{
	  Empty_INDEX++;
	  Person* new_Person = new Person;
	  listing.push_back(new_Person);
	  //	  cout << "i\'m in add!!!\n";
	  if (listing.size() != 1)
	    data_input(*(listing.end() - 1), *(listing.end() - 2));
	  else
	    data_input(*(listing.end() - 1), *(listing.end() - 1));
	}
      if (Input_Information.compare("list") == 0)
	{
	  Empty_INDEX++;
	  if (listing.size() != 0)
	    print_all_input(listing);
	  else
	    cout << "No Person in list, please use \"add\" to add new Person.\n";
	}
      if (Input_Information.compare("clean") == 0)
	{
	  Empty_INDEX++;
	  if (listing.size() != 0)
	    {
	      cout << "id? ";
	      cin >> Input_Information;
	      if (Input_Information.compare("*") == 0)
		delete_all_input(listing);
	      else
		{	  
		  int cleaning_INDEX = atoi (Input_Information.c_str());
		  if(cleaning_INDEX >= 0)
		    delete_input(cleaning_INDEX, listing);
		  else
		    cout << "Type number of Person who you want to delete, or type \"*\" to delete all input Persons.\n";
		}
	    }
	  else
	    cout << "No Person in list, please use \"add\" to add new Person.\n";
	}
      if (Input_Information.size() == 0)
	{
	  cout << "Type some one-word command what i know, please.\n";
	  continue;
	}
    }
  out_print("out.xml", listing);
  delete_all_input(listing);
  cout << "I\'m quiting...\n";
  return 0;
}
