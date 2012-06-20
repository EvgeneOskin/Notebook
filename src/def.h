#ifndef def_H__
#define def_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <sqlite3.h>
#include "Person.h"
//add namespace person

void out_print_all(sqlite3 *out_db, std::vector<Person*> &List);
void out_print(sqlite3 *out_db, std::vector<Person*> &List, unsigned int out_Person_INDEX);
void input_old_data(sqlite3 *out_db, std::vector<Person*> &List);
void data_input(Person* new_Person, int new_ID);
void clean_input(int &delete_INDEX, std::vector<Person*> &List);
void delete_input(int &delete_INDEX, std::vector<Person*> &List);
void clean_all(std::vector<Person*> &List);
void delete_all(std::vector<Person*> &List);
unsigned int print_input(std::vector<Person*> &List);
unsigned int print_all(std::vector<Person*> &List);
void analyze_Phone(unsigned short int goodness_INDEX, Person* analyze_Person);
void analyze_Age(unsigned short int goodness_INDEX, Person* analyze_Person);
unsigned short int analyze_input(std::string &analyzed_str, std::vector<Person*> &listing, sqlite3 *out_db);
#endif // def_H__
