#include "def_note.h"

using namespace std;

void out_print(string out_file_name, vector<Person*> &List)
{
  ofstream out_file (out_file_name.c_str());
  out_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
	   << "<Contact_List>\n";\
  vector<Person*>::iterator list_iterator;
  for (list_iterator = List.begin();  list_iterator < List.end(); list_iterator++)
    {
      out_file << "  <Person "
	       << "Age=\"" << (*list_iterator)->Age << "\" "
	       << "Name=\"" << analyze((*list_iterator)->Name) << "\" "
	       << "Second_Name=\"" << analyze((*list_iterator)->Second_Name) << "\" "
	       << "Phone=\"" << analyze((*list_iterator)->Phone) << "\" "
	       << "Notes=\"" << analyze((*list_iterator)->Notes) << "\" "
	       << ">" << (*list_iterator)->ID << "</Person>\n";
    }
  out_file << "</Contact_List>";
  out_file.close();
  return;
}
void data_input(Person* new_Person, Person* last_Person)
{
  new_Person->ID = last_Person->ID + 1;
  string Input_Information;
  cout << "Creating a new contact:\nAge: ";
  cin >> Input_Information;
  new_Person->add_Age(atoi(Input_Information.c_str()));
  cout << "Name: ";
  cin >> Input_Information;
  new_Person->add_Name(Input_Information);
  cout << "Second name: ";
  cin >> Input_Information;
  new_Person->add_Second_Name(Input_Information);
  cout << "Phone: ";
  cin >> Input_Information;
  new_Person->add_Phone(Input_Information);
  cout << "Notes: ";
  cin >> Input_Information;
  new_Person->add_Notes(Input_Information);
}

void delete_input(int &delete_INDEX, std::vector<Person*> &List)
{
  if (delete_INDEX < List.size())
    {
      vector<Person*>::iterator delete_iterator = List.begin()+delete_INDEX-1;
      cout<< "i\'m cleaning with ID = " << (*delete_iterator)->ID << '\n';
      delete (*delete_iterator);
      List.erase(delete_iterator);
    }
  return;
}

void delete_all_input(vector<Person*> &List)
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

void print_all_input(vector<Person*> &List)
{
  vector<Person*>::iterator list_iterator;
  for (list_iterator = List.begin();  list_iterator < List.end(); list_iterator++)
    cout << "print Person\'s data with ID: " << (*list_iterator)->ID << '\n'
	 << "Age: " << (*list_iterator)->Age << '\n'
	 << "Name: " << (*list_iterator)->Name << '\n'
	 << "Second Name: " << (*list_iterator)->Second_Name << '\n'
	 << "Phone: " << (*list_iterator)->Phone << '\n'
	 << "Notes: " << (*list_iterator)->Notes << '\n';
  return;
}

string analyze(string &in_str)
{
  string out_str;
  string::iterator str_iterator;
  for (str_iterator = in_str.begin(); str_iterator < in_str.end(); str_iterator++)
    switch (*str_iterator)
      {
      case '&': out_str += "&amp;"; break;
      case '<': out_str += "&lt;"; break;
      case '>': out_str += "&gt;"; break;
      case '\'': out_str += "&apos;"; break;
      case '\"': out_str += "&quot;"; break;
      default:  out_str += *str_iterator;
      }
  return out_str;
}
