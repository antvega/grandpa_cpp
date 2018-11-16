#include <string>
using namespace std;
#pragma once

struct movieNode{
  string name;
  string location;
  int date;
  string kind;
public:
  movieNode(string name1,string location1,int date1,string kind1){
    name = name1;
    location = location1;
    date = date1;
    kind = kind1;
  }
};
