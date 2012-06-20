#include "def.h"
#include "Person.h"
using namespace std;

void analyze_Phone(unsigned short int goodness_INDEX, Person *analyzed_Person)
{
  if (goodness_INDEX == 0)
    {
      cout << "\033[0,31m   You typed Phone, which do not consist of only [0-9] or not-first \'-\' or fist \'+\'.\033[0m\n"
	   << "   But I can give you a second chanse...\n \033[0,34m   Try again? (\'y\' to confim, smth else to abort)  \033[0m";

      string Input_Information;
      getline(cin, Input_Information);
      
      if ( Input_Information.compare("y") == 0)
	{
	  cout << "Phone: ";
	  getline(cin, Input_Information);
	  analyze_Phone(analyzed_Person->add_Phone(Input_Information), analyzed_Person);
	}
      else
	{
	  cout << "   OK, I will think that you typed senseless information about Phone of Person."
	       <<" Phone will be \"\".\n";
	  analyzed_Person->Phone  = "";
	}	  
    }
  return;
}

void analyze_Age(unsigned short int goodness_INDEX, Person *analyzed_Person)
{
  if (goodness_INDEX == 0)
    {
      cout << "\033[0,31m   Did you input \"zero\" age, did you?\n\033[0,34m"
	   << " (\'y\' to confim, smth else to abort)  \033[0m";
      string Input_Information;
      getline(cin, Input_Information);
      
      if ( Input_Information.compare("y") == 0)
	analyzed_Person->Age = 0;
      else
	{
	  cout << "   Are you want try again?\n\033[0,34m"
	       << " (\'y\' to confim, smth else to abort)  \033[0m";
	  getline(cin, Input_Information);
	  
	  if ( Input_Information.compare("y") == 0)
	    {
	      cout << "Age: ";
	      getline(cin, Input_Information);
	      analyze_Age(analyzed_Person->add_Age(atoi(Input_Information.c_str())), analyzed_Person);
	    }
	  else
	    {
	      cout << "   OK, I will think that you typed senseless information about Age of Person."
		   << " Age will be \033[0,34m\"zero\"\033[0m.\n";
	      analyzed_Person->Age = 0;
	    }
	}
    }
  
  if (goodness_INDEX == 2)
    {
      cout << "\033[0,31m   You inputed negative Age (how is it posible?!).\n"
	   << " \033[0,34mTry again? (\'y\' to confim, smth else to abort)  \033[0m ";
      string Input_Information;
      getline(cin, Input_Information);

      if ( Input_Information.compare("y") == 0)
	{
	  cout << "Age: ";
	  getline(cin, Input_Information);
	  analyze_Age(analyzed_Person->add_Age(atoi(Input_Information.c_str())), analyzed_Person);		
	}
      else
	{
	  cout << "   OK, I will think that you typed senseless information about Age of Person."
	       << " Age will be \033[0,34m\"zero\"\033[0m.\n";
	  analyzed_Person->Age = 0;
	}
    }
}


unsigned short int analyze_input(string &analyzed_str, vector<Person*> &listing, sqlite3 *out_db)
{
  unsigned short int What_need_to_be_done_INDEX = 0;

  if (analyzed_str.compare("add") == 0)
    {
      What_need_to_be_done_INDEX++;
      Person* new_Person = new Person;
      listing.push_back(new_Person);

      if (listing.size() != 1)
	data_input(*(listing.end() - 1), (*(listing.end() - 2))->ID);
      else
	data_input(*(listing.end() - 1), (*(listing.end() - 1))->ID);
    }
  
  if (analyzed_str.compare("list_all") == 0)
    {
      What_need_to_be_done_INDEX++;
      if (listing.size() != 0)
	print_all(listing);
      else
	cout << "   No Person in list, please use \"add\" to add new Person.\n";
    }
  if (analyzed_str.compare("list_last") == 0)
    {
      What_need_to_be_done_INDEX++;
      if (print_input(listing) == 0)
	cout << "   You do not enter a Person, please use \"add\" to add new Person.\n";
    }

  if (analyzed_str.compare("clean") == 0)
    {
      What_need_to_be_done_INDEX++;

      if (listing.size() != 0)
	{
	  cout << "number of input? ";
	  getline(cin, analyzed_str);

	  if (analyzed_str.compare("*") == 0)
	    clean_all(listing);
	  else
	    {	  
	      int cleaning_INDEX = atoi (analyzed_str.c_str());

	      if(cleaning_INDEX > 0)
		clean_input(cleaning_INDEX, listing);
	      else
		cout << "   Type number of Person who you want to clean, or type \"*\" to clean all inputed Persons.\n";
	    }
	}
      else
	cout << "   No Person in list, please use \"add\" to add new Person.\n";
    }
  if (analyzed_str.compare("delete") == 0)
    {
      What_need_to_be_done_INDEX++;
      
      if (listing.size() != 0)
	{

	  cout << "number of input? ";
	  getline(cin, analyzed_str);
	  
	  if (analyzed_str.compare("*") == 0)
	    delete_all(listing);
	  else
	    {	  
	      int deleting_INDEX = atoi (analyzed_str.c_str());
	      
	      if(deleting_INDEX > 0)
		delete_input(deleting_INDEX, listing);
	      else
		cout << "   Type number of Person who you want to delete, or type \"*\" to delete all inputed Persons.\n";
	    } 
	}
      else
	cout << "   No Person in list, please use \"add\" to add new Person.\n";

    }
  if (analyzed_str.compare("save") == 0)
    {
      What_need_to_be_done_INDEX++;
      if (listing.size() != 0)
	{
	  cout << "number of input? ";
	  getline(cin, analyzed_str);

	  if (analyzed_str.compare("*") == 0)
	    out_print_all(out_db, listing);
	  else
	    {
	      int print_INDEX = atoi (analyzed_str.c_str());
	      if(print_INDEX > 0)
		out_print(out_db, listing, print_INDEX);
	      else
		cout << "   Type number of Person who you want to save, or type \"*\" to save all input Persons.\n";
	    }
	}
      else
	cout << "   No Person in list, please use \"add\" to add new Person.\n";
    }

  if (analyzed_str.compare("quit") == 0)
    What_need_to_be_done_INDEX += 2;;

  if ((analyzed_str.size() == 0) || (What_need_to_be_done_INDEX == 0))
    {
      cout << "   Type some one-word command what I know, please.\n";
    }

  return What_need_to_be_done_INDEX;
}
