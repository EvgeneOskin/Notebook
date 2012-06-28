#ifndef def_H__
#define def_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <sqlite3.h>
#include "boost/lexical_cast.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/foreach.hpp"
#include "Person.h"
//add namespace person

typedef std::vector<boost::shared_ptr<Person> > person_v;

void out_print_all(sqlite3 *out_db, person_v &List);
void out_print(sqlite3 *out_db, person_v &List, unsigned int out_Person_INDEX);
void input_old_data(sqlite3 *out_db, person_v &List);
void data_input(Person* new_Person, int new_ID);
void clean_input(int &delete_INDEX, person_v &List);
void delete_input(int &delete_INDEX, person_v &List);
void clean_all(person_v &List);
void delete_all(person_v &List);
unsigned int print_input(person_v &List);
unsigned int print_all(person_v &List);
void analyze_Phone(unsigned short int goodness_INDEX, Person* analyze_Person);
void analyze_Age(unsigned short int goodness_INDEX, Person* analyze_Person);
unsigned short int analyze_input(std::string &analyzed_str, person_v &listing, sqlite3 *out_db);
#endif // def_H__
