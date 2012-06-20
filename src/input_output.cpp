#include "def.h"
#include "Person.h"

using namespace std;

void out_print_all(sqlite3 *out_db, vector<Person*> &List)
{
  int sqlite_Error_INDEX;
  unsigned int   ID_counter = 0;
  sqlite3_stmt *out_sqlite_stmt;
  stringstream SQL_out_statment(stringstream::out);
  vector<Person*>::iterator out_iterator;

  sqlite_Error_INDEX = sqlite3_prepare(out_db,
          "CREATE TABLE Person_list(ID INTEGER, Age INTEGER, Name TEXT, Second_Name TEXT, Phone TEXT, Notes TEXT);",
	  -1, &out_sqlite_stmt, NULL);
  sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
  do
    {
      ID_counter++;
    }
  while (sqlite3_reset(out_sqlite_stmt) == SQLITE_DONE);
  ID_counter -= 1;
  for (out_iterator = List.begin(); out_iterator < List.end(); out_iterator++)
    {
      (*out_iterator)->ID = ID_counter;
      ID_counter++;
      if (!((*out_iterator)->Save_Flag))
	{
	  (*out_iterator)->ID = ID_counter;
	  ID_counter++;
	  SQL_out_statment << "INSERT INTO Person_list (ID, Age, Name, Second_Name, Phone, Notes) VALUES ("
			   << (*out_iterator)->ID << ", "
			   << (*out_iterator)->Age << ", '"
			   << (*out_iterator)->Name << "', '"
			   << (*out_iterator)->Second_Name << "', '"
			   << (*out_iterator)->Phone << "', '"
			   << (*out_iterator)->Notes << "');";
	  (*out_iterator)->Save_Flag = true;
	  //      cout << SQL_out_statment.str().c_str() << '\n';
	  sqlite_Error_INDEX = sqlite3_prepare(out_db, SQL_out_statment.str().c_str(), -1, &out_sqlite_stmt, NULL);
	  //	  cout << sqlite_Error_INDEX << '\t';
	  sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
	  //	  cout << sqlite_Error_INDEX << '\n';
	  SQL_out_statment.str(string());
	  SQL_out_statment.clear();
	}
    }
      sqlite3_reset(out_sqlite_stmt);
      return;
}

void out_print(sqlite3 *out_db, vector<Person*> &List, unsigned int out_Person_INDEX)
{

  if (out_Person_INDEX <= List.size())
    {
      vector<Person*>::iterator out_iterator = List.begin() + out_Person_INDEX -1;	  
      if (!((*out_iterator)->Save_Flag))
	{
	    int sqlite_Error_INDEX;
	    sqlite3_stmt *out_sqlite_stmt;
	    stringstream SQL_out_statment(stringstream::out);
	    sqlite_Error_INDEX = sqlite3_prepare(out_db,
	     "CREATE TABLE Person_list(ID INTEGER, Age INTEGER, Name TEXT, Second_Name TEXT, Phone TEXT, Notes TEXT);",
						 -1, &out_sqlite_stmt, NULL);
	    sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
	    sqlite3_reset(out_sqlite_stmt);

	    (*out_iterator)->ID = + 1;
	    SQL_out_statment << "INSERT INTO Person_list (ID, Age, Name, Second_Name, Phone, Notes) VALUES ("
			     << (*out_iterator)->ID << ", "
			     << (*out_iterator)->Age << ", "
			     << (*out_iterator)->Name << ", "
			     << (*out_iterator)->Second_Name << ", "
			     << (*out_iterator)->Phone << ", "
			     << (*out_iterator)->Notes << ");";
	    (*out_iterator)->Save_Flag = true;
	    sqlite_Error_INDEX = sqlite3_prepare(out_db, SQL_out_statment.str().c_str(), -1, &out_sqlite_stmt, NULL);
	    sqlite_Error_INDEX = sqlite3_step(out_sqlite_stmt);
	    sqlite3_reset(out_sqlite_stmt);
	    SQL_out_statment.str(string());
	    SQL_out_statment.clear();
	}
      else
	{
	  cout << "It's already saved";
	}
    }
  return;
}

void input_old_data(sqlite3 *out_db, vector<Person*> &List)
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
	  Person* new_Person = new Person;
	  List.push_back(new_Person);
	  (*(List.end() - 1))->Save_Flag = true;
	  (*(List.end() - 1))->Database_Flag = true;

	  (*(List.end() - 1))->ID = sqlite3_column_int(out_sqlite_stmt, 0);
	  
	  (*(List.end() -1))->add_Age(sqlite3_column_int(out_sqlite_stmt, 1));

	  Input_Information = string((char*)sqlite3_column_text(out_sqlite_stmt, 2));
	  (*(List.end() - 1))->add_Name(Input_Information);

	  Input_Information = string((char*)sqlite3_column_text(out_sqlite_stmt, 3));
	  (*(List.end() - 1))->add_Second_Name(Input_Information);

	  Input_Information = string((char*)sqlite3_column_text(out_sqlite_stmt, 4));
	  (*(List.end() - 1))->add_Phone(Input_Information);

	  Input_Information = string((char*)sqlite3_column_text(out_sqlite_stmt, 5));
	  (*(List.end() - 1))->add_Notes(Input_Information);
	}
      
    }
  while (sqlite_Error_INDEX != SQLITE_DONE);
  sqlite3_reset(out_sqlite_stmt);
  return;
}
void data_input(Person* new_Person, int new_ID)
{
  new_Person->ID = new_ID + 1;
  string Input_Information;

  cout << "   Creating a new contact:\nAge: ";
  getline(cin, Input_Information);
  analyze_Age(new_Person->add_Age(atoi(Input_Information.c_str())),new_Person);

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
}


void clean_input(int &delete_INDEX, vector<Person*> &List)
{
  unsigned int counter = 0;
  vector<Person*>::iterator delete_iterator;
  for (delete_iterator = List.end() - 1;  delete_iterator >= List.begin(); delete_iterator--)
    {
      if (!((*delete_iterator)->Database_Flag))
	{
	  counter++;
	  if (counter == delete_INDEX)
	    {
	      cout << "   i\'m cleaning Person with number in input " << delete_INDEX << '\n';
	      delete (*delete_iterator);
	      List.erase(delete_iterator);
	      return;
	    }
	}
    }
  cout << "   i can not find Person with number in input" << delete_INDEX << "\n";
  return ;
}


void delete_input(int &delete_INDEX, vector<Person*> &List)
{
  if (delete_INDEX <= List.size())
    {
      vector<Person*>::iterator delete_iterator = List.begin()+delete_INDEX-1;
      cout<< "   i\'m deleting Person with number in database " << delete_INDEX << '\n';
      delete (*delete_iterator);
      List.erase(delete_iterator);
    }
  else
    cout << "   i can not find Person with number in database" << delete_INDEX << "\n";
  return;
}

void clean_all(vector<Person*> &List)
{
  vector<Person*>::iterator delete_iterator;
  for (delete_iterator = List.end() - 1;  delete_iterator >= List.begin(); delete_iterator--)
    {
      if (!((*delete_iterator)->Database_Flag))
	{
	  delete (*delete_iterator);
	  List.erase(delete_iterator);
	}
    }
  return;
}

void delete_all(vector<Person*> &List)
{
  if (List.size() != 0)
    {
      vector<Person*>::iterator list_iterator;
      for (list_iterator = List.begin();  list_iterator < List.end(); list_iterator++)
	delete (*list_iterator);
      List.clear();
    }
  return;
}

unsigned int print_all(vector<Person*> &List)
{
  vector<Person*>::iterator list_iterator;
  unsigned int counter = 0;
  for (list_iterator = List.begin();  list_iterator < List.end(); list_iterator++)
    {
      counter++;
      cout << counter << ") Print Person\'s data: " << '\n'
	   << "   Age: " << (*list_iterator)->Age << '\n'
	   << "   Name: " << (*list_iterator)->Name << '\n'
	   << "   Second Name: " << (*list_iterator)->Second_Name << '\n'
	   << "   Phone: " << (*list_iterator)->Phone << '\n'
	   << "   Notes: " << (*list_iterator)->Notes << '\n';
    }
  return counter;
}

unsigned int print_input(vector<Person*> &List)
{
  vector<Person*>::iterator list_iterator;
  unsigned int counter = 0;
  for (list_iterator = List.begin();  list_iterator < List.end(); list_iterator++)
    {
      if (!((*list_iterator)->Database_Flag))
	{
	  counter++;
	  cout << counter << ") Print Person\'s data: " << '\n'
	       << "   Age: " << (*list_iterator)->Age << '\n'
	       << "   Name: " << (*list_iterator)->Name << '\n'
	       << "   Second Name: " << (*list_iterator)->Second_Name << '\n'
	       << "   Phone: " << (*list_iterator)->Phone << '\n'
	       << "   Notes: " << (*list_iterator)->Notes << '\n';
	}
    }
  return counter;
}
