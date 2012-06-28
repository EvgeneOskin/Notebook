#include "../src/Person.h"
#include "gtest_files/include/gtest/gtest.h"

Person test_Person;
std::string test_str;

TEST(Person, add_Name)
{
  test_str = "";
  EXPECT_EQ (0, test_Person.add_Name(test_str));
  test_str = "BlaBla";
  EXPECT_EQ (1, test_Person.add_Name(test_str));
}

TEST(Person, add_Second_Name)
{
  test_str = "";
  EXPECT_EQ (0, test_Person.add_Second_Name(test_str));
  test_str = "BlaBlaBla";
  EXPECT_EQ (1, test_Person.add_Second_Name(test_str));
}

TEST(Person, add_Age)
{  EXPECT_EQ (1, test_Person.add_Age(1));
  EXPECT_EQ (1, test_Person.add_Age(200));
  EXPECT_EQ (0, test_Person.add_Age(-2));
  EXPECT_EQ (1, test_Person.add_Age(0));
}

TEST(Person, add_Phone)
{  test_str = "8-8955-69-985-54";
  EXPECT_EQ (1, test_Person.add_Phone(test_str));
  test_str = "468-987-987";
  EXPECT_EQ (1, test_Person.add_Phone(test_str));
  test_str = "blkdshoe";
  EXPECT_EQ (0, test_Person.add_Phone(test_str));
}

