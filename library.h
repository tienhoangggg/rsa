#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class number
{
private:
    string value;
public:
    number(){value = "";}
    number(string);
    number(int);
    string get_value();
    bool operator < (number);
    bool operator > (number);
    bool operator <= (number);
    bool operator == (number);
    bool mod2();
    number operator = (number);
    number operator + (number);
    number operator - (number);
    number operator * (number);
    number operator / (number);
    number operator % (number);
};