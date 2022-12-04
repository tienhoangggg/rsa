#pragma once
#include <iostream>
#include <time.h>
#include <random>
#include <string>
#include <vector>
#include <thread>
using namespace std;

class number
{
private:
	vector<int> value;

public:
	number() {}
	number(int);
	string get_value();
	bool operator<(number);
	bool operator>(number);
	bool operator<=(number);
	bool operator==(number);
	bool mod2();
	number operator=(number);
	number operator+(number);
	number operator-(number);
	number operator*(number);
	number operator/(number);
	number operator%(number);
};
typedef number X;
#define base 1000000;
void generateBigPrime(int k, int bits, vector<X> *primes, int);
X inverse(X a, X b);