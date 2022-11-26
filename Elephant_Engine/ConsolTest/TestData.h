#pragma once
#include <ctime>
#include <vector>
#include <string>
#include <unordered_map>
#include "ITableData.h"

class TestData : public ITableData
{
 public:
  int id;
  bool test1;
  short test2;
  unsigned short test3;
  int test4;
  unsigned int test5;
  float test6;
  double test7;
  std::tm test8;
  char test9;
  unsigned char test10;
  std::string test11;
  std::vector<bool> test12;
  std::vector<short> test13;
  std::vector<unsigned short> test14;
  std::vector<int> test15;
  std::vector<unsigned int> test16;
  std::vector<float> test17;
  std::vector<double> test18;
  std::vector<std::tm> test19;
  std::vector<char> test20;
  std::vector<unsigned char> test21;
  std::vector<std::string> test22;

 public:
  virtual void Serialize(std::unordered_map<std::string, std::string>& data);
};
