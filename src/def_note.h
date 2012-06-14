#ifndef PERSON_H__
#define PERSON_H__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

class Person
{
 public:
  unsigned int ID;
  short int Age;
  std::string Name;
  std::string Second_Name;
  std::string Phone;
  std::string Notes;
  Person();
  ~Person();
  unsigned short int add_Age(int new_Age);
  unsigned short int add_Name(std::string &new_Name);
  unsigned short int add_Second_Name(std::string &new_Second_Name);
  unsigned short int add_Phone(std::string &new_Phone);
  unsigned short int add_Notes(std::string &new_Notes);
};

void out_print(std::string out_file_name, std::vector<Person*> &List);
void data_input(Person* new_Person, Person* last_Person);
void print_all_input(std::vector<Person*> &List);
void delete_all_input(std::vector<Person*> &List);
void delete_input(int &delete_INDEX, std::vector<Person*> &List);
std::string analyze(std::string &in_str);
#endif // PERSON_H__
