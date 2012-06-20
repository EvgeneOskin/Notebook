#include "def.h"
#include "Person.h"

using namespace std;

int main (int argc, char* argv[])
{
  sqlite3 *out_db;
  int sqlite_Error_INDEX;
  string Input_Information;
  vector <Person*> listing;
  cout << "Hello, type some one-word command for me.\n";
  sqlite_Error_INDEX = sqlite3_initialize();
  sqlite_Error_INDEX = sqlite3_open("notelist.db3", &out_db);
  input_old_data(out_db, listing);
  do
    {
      cout << "# ";
      getline(cin, Input_Information);  
    }
  while ( analyze_input(Input_Information, listing, out_db) != 2);

  out_print_all(out_db, listing);
  cout << "   I\'m quiting...\n";
  sqlite3_close(out_db);
  sqlite3_shutdown();
  delete_all(listing);
  return 0;
}
