#include "def.h"
#include "Person.h"
using namespace std;

void out_print_all(sqlite3 *out_db, person_v  &List)
{
  int sqlite_Error_INDEX;
  unsigned int   ID_counter = 0;
  sqlite3_stmt *out_sqlite_stmt;
  stringstream SQL_out_statment(stringstream::out);

  sqlite_Error_INDEX = sqlite3_prepare(out_db,
          "CREATE TABLE Person_list(ID INTEGER, Age INTEGER, Name TEXT, Second_Name TEXT, Phone TEXT, Notes TEXT);",
	  -1, &out_sqlite_stmt, NULL);
  sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
  do
    {
      ID_counter++;
    }
  while (sqlite3_reset(out_sqlite_stmt) == SQLITE_DONE);
  ID_counter--;

  BOOST_FOREACH(boost::shared_ptr<Person> printed_Person, List)
    {
      (printed_Person.get())->ID = ID_counter;
      ID_counter++;
      if (!((printed_Person.get())->Save_Flag))
	{
	  SQL_out_statment << "INSERT INTO Person_list(ID, Age, Name, Second_Name, Phone, Notes) VALUES ("
			   << (printed_Person.get())->ID << ", "
			   << (printed_Person.get())->Age << ", '"
			   << (printed_Person.get())->Name << "', '"
			   << (printed_Person.get())->Second_Name << "', '"
			   << (printed_Person.get())->Phone << "', '"
			   << (printed_Person.get())->Notes << "');";
	  (printed_Person.get())->Save_Flag = true;
	  sqlite_Error_INDEX = sqlite3_prepare(out_db, SQL_out_statment.str().c_str(), -1, &out_sqlite_stmt, NULL);
	  sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
	  SQL_out_statment.str(string());
	  SQL_out_statment.clear();
	}
    }
  sqlite3_reset(out_sqlite_stmt);
  return;
}

void out_print(sqlite3 *out_db, person_v &List, unsigned int out_Person_INDEX)
{
  unsigned int counter = 0;
  BOOST_FOREACH(boost::shared_ptr<Person> printed_Person, List)
    {
      if (!((printed_Person.get())->Database_Flag))
	{
	  counter++;	      
	  if(counter == out_Person_INDEX)
	    {
	      if (!((printed_Person.get())->Save_Flag))
		{
		  (printed_Person.get())->Save_Flag = true;
		  int sqlite_Error_INDEX;
		  sqlite3_stmt *out_sqlite_stmt;
		  stringstream SQL_out_statment(stringstream::out);
		  sqlite_Error_INDEX = sqlite3_prepare(out_db,
          "CREATE TABLE Person_list(ID INTEGER, Age INTEGER, Name TEXT, Second_Name TEXT, Phone TEXT, Notes TEXT)",
	  -1, &out_sqlite_stmt, NULL);
		  sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
		  
		  (printed_Person.get())->ID += 1;
		  SQL_out_statment << "INSERT INTO Person_list(ID, Age, Name, Second_Name, Phone, Notes) VALUES ("
				   << (printed_Person.get())->ID << ", "
				   << (printed_Person.get())->Age << ", '"
				   << (printed_Person.get())->Name << "', '"
				   << (printed_Person.get())->Second_Name << "', '"
				   << (printed_Person.get())->Phone << "', '"
				   << (printed_Person.get())->Notes << "')";
		  sqlite_Error_INDEX = sqlite3_prepare(out_db, SQL_out_statment.str().c_str(), -1, &out_sqlite_stmt, NULL);
		  sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
		  sqlite3_reset(out_sqlite_stmt);
		  cout << " I saved it\n";
		}
	      else
		cout << "   It's already saved\n";
	      return;
	    }
	}
    }
  return;
}

void input_old_data(sqlite3 *out_db, person_v &List)
{
  int sqlite_Error_INDEX;
  sqlite3_stmt *out_sqlite_stmt;
  string Input_Information;
  sqlite_Error_INDEX = sqlite3_prepare(out_db,
	     "CREATE TABLE Person_list(ID INTEGER, Age INTEGER, Name TEXT, Second_Name TEXT, Phone TEXT, Notes TEXT);",
				       -1, &out_sqlite_stmt, NULL);
  sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);

  sqlite_Error_INDEX = sqlite3_prepare(out_db, "select * from Person_list;", -1, &out_sqlite_stmt, NULL);
  do
    {
      sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
      if( sqlite_Error_INDEX!= SQLITE_DONE)
	{
	  List.push_back(boost::shared_ptr<Person>(new Person()));

	  ((List.end() - 1)->get())->Save_Flag = true;
	  ((List.end() - 1)->get())->Database_Flag = true;

	  ((List.end() - 1)->get())->ID = sqlite3_column_int(out_sqlite_stmt, 0);
	  
	  ((List.end() - 1)->get())->add_Age(sqlite3_column_int(out_sqlite_stmt, 1));

	  Input_Information = string((char*)sqlite3_column_text(out_sqlite_stmt, 2));
	  ((List.end() - 1)->get())->add_Name(Input_Information);

	  Input_Information = string((char*)sqlite3_column_text(out_sqlite_stmt, 3));
	  ((List.end() - 1)->get())->add_Second_Name(Input_Information);

	  Input_Information = string((char*)sqlite3_column_text(out_sqlite_stmt, 4));
	  ((List.end() - 1)->get())->add_Phone(Input_Information);

	  Input_Information = string((char*)sqlite3_column_text(out_sqlite_stmt, 5));
	  ((List.end() - 1)->get())->add_Notes(Input_Information);
	}
      
    }
  while (sqlite_Error_INDEX != SQLITE_DONE);
  sqlite3_reset(out_sqlite_stmt);
  return;
}
void data_input(Person* new_Person, int new_ID)
{
  string Input_Information;

  cout << "   Creating a new contact:\nAge: ";
  getline(cin, Input_Information);

  int casted_Age = 0;
  try
    {
      casted_Age = boost::lexical_cast<int>(Input_Information);
    }
  catch (exception& e)
    {
      cout << "you type not a number, please try again" << endl;
      data_input(new_Person, new_ID);
      return;
    }
  analyze_Age(new_Person->add_Age(casted_Age), new_Person);

  cout << "Name: ";
  getline(cin, Input_Information);
  new_Person->add_Name(Input_Information);

  cout << "Second name: ";
  getline(cin, Input_Information);
  new_Person->add_Second_Name(Input_Information);

  cout << "Phone: ";
  getline(cin, Input_Information);
  analyze_Phone(new_Person->add_Phone(Input_Information), new_Person);

  cout << "Notes: ";
  getline(cin, Input_Information);
  new_Person->add_Notes(Input_Information);

  new_Person->ID = new_ID + 1;

}


void clean_input(int &delete_INDEX, person_v &List)
{
  unsigned int counter = 0;
  person_v::iterator delete_iterator;
  for (delete_iterator = List.end() - 1;  delete_iterator >= List.begin(); delete_iterator--)
    {
      if (!((delete_iterator->get())->Database_Flag))
	{
	  counter++;
	  if (counter == delete_INDEX)
	    {
	      cout << "   i\'m cleaning Person with number in input " << delete_INDEX << '\n';
	      List.erase(delete_iterator);
	      return;
	    }
	}
    }
  cout << "   i can not find Person with number in input" << delete_INDEX << "\n";
  return ;
}


void delete_input(int &delete_INDEX, person_v &List)
{
  if (delete_INDEX <= List.size())
    {
      person_v::iterator delete_iterator = List.begin() + delete_INDEX - 1;
      cout<< "   i\'m deleting Person with number in database " << delete_INDEX << '\n';
      List.erase(delete_iterator);
    }
  else
    cout << "   i can not find Person with number in database" << delete_INDEX << "\n";
  return;
}

void clean_all(person_v &List)
{
  person_v::iterator delete_iterator;
  for (delete_iterator = List.end() - 1;  delete_iterator >= List.begin(); delete_iterator--)
    {
      if (!((delete_iterator->get())->Database_Flag))
	{
	  List.erase(delete_iterator);
	}
    }
  return;
}

void delete_all(person_v &List)
{
  if (!List.empty())
    {
      List.clear();
    }
  return;
}

unsigned int print_all(person_v &List)
{
  unsigned int counter = 0;
  BOOST_FOREACH(boost::shared_ptr<Person> printed_Person, List)
    {
      counter++;
      cout << counter << ") Print Person\'s data: " << '\n'
	   << "   Age: " << (printed_Person.get())->Age << '\n'
	   << "   Name: " << (printed_Person.get())->Name << '\n'
	   << "   Second Name: " << (printed_Person.get())->Second_Name << '\n'
	   << "   Phone: " << (printed_Person.get())->Phone << '\n'
	   << "   Notes: " << (printed_Person.get())->Notes << '\n';
    }
  return counter;
}

unsigned int print_input(person_v &List)
{
  unsigned int counter = 0;
  BOOST_FOREACH(boost::shared_ptr<Person> printed_Person, List)
    {
      if (!((printed_Person.get())->Database_Flag))
	{
	  counter++;
	  cout << counter << ") Print Person\'s data: " << '\n'
	       << "   Age: " << (printed_Person.get())->Age << '\n'
	       << "   Name: " << (printed_Person.get())->Name << '\n'
	       << "   Second Name: " << (printed_Person.get())->Second_Name << '\n'
	       << "   Phone: " << (printed_Person.get())->Phone << '\n'
	       << "   Notes: " << (printed_Person.get())->Notes << '\n';
	}
    }
  return counter;
}
