#ifndef PERSON_H__
#define PERSON_H__
#include <string>
#include <iostream>

class Person
{
 public:
  unsigned int ID;
  short int Age;
  std::string Name;
  std::string Second_Name;
  std::string Phone;
  std::string Notes;
  bool Save_Flag;
  bool Database_Flag;
  Person();
  ~Person();
  unsigned short int add_Age(int new_Age);
  unsigned short int add_Name(std::string &new_Name);
  unsigned short int add_Second_Name(std::string &new_Second_Name);
  unsigned short int add_Phone(std::string &new_Phone);
  unsigned short int add_Notes(std::string &new_Notes);
};
#endif //PERSON_H__
