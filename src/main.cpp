#include "def.h"
#include "Person.h"

using namespace std;

int main (int argc, char* argv[])
{
  sqlite3 *out_db;
  int sqlite_Error_INDEX;
  string Input_Information;
  person_v listing;
  cout << "Hello, type some one-word command for me.\n";
  sqlite_Error_INDEX = sqlite3_initialize();
  sqlite_Error_INDEX = sqlite3_open("notelist.db3", &out_db);
  input_old_data(out_db, listing);
  //  unsigned int count = 0;
  //unsigned int mini_count;
  do
    {
      cout << "# ";
      getline(cin, Input_Information);
      //      cout << ++count << endl;
      //     mini_count = 0;
      //      person_v::iterator list_iterator;
      // for (list_iterator = listing.begin();  list_iterator < listing.end(); list_iterator++)
      //	cout << "dbg<<< " << ++mini_count<<" meet "<< list_iterator->use_count() << " times"<< endl ;

    }
  while ( analyze_input(Input_Information, listing, out_db) != 2);

  out_print_all(out_db, listing);
  cout << "   I\'m quiting...\n";
  sqlite3_close(out_db);
  sqlite3_shutdown();
  delete_all(listing);
  return 0;
}
