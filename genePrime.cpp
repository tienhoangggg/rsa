#include "library.h"

X pow(X a, X m, X n)
{
	X result = 1;
	while (m > 0)
	{
		if (!m.mod2())
			result = result * a % n;
		m = m / 2;
		a = a * a % n;
	}
	return result;
}

bool test(int s, X m, X n, X a)
{
	X p = pow(a, m, n);
	if (p == 1)
		return true;
	a = n - 1;
	while (s--)
	{
		if (p == a)
			return true;
		p = p * p % n;
	}
	return false;
}

bool Check_miller(X n, int k)
{
	int s = 0;
	X d = n - 1;
	while (d.mod2())
	{
		s += 1;
		d = d / 2;
	}
	X range = n - 2;
	while (k--)
	{
		X a = X(rand()) % (n - 2) + 2;
		if (!test(s, d, n, a))
			return false;
	}
	return true;
}

X binToNum(vector<int> num)
{
	X n = 0, pow_2 = 1;
	for (int i = num.size() - 1; i >= 0; --i)
	{
		n = n + (pow_2 * num[i]);
		pow_2 = pow_2 * 2;
	}
	return n;
}

void generateBigPrime(int k, int bits, vector<X> *prime, int stateRand)
{
	X _num;
	srand(time(NULL));
	vector<int> _bin(bits, 0);
	_bin[0] = 1;
	_bin[bits - 1] = 1;
	int baseRand = stateRand + 3;
	while (1)
	{
		for (int i = 1; i < bits - 1; ++i)
		{
			_bin[i] = (rand() + baseRand) % 2;
			for (int j = 0; j < stateRand; j++)
				baseRand = (((baseRand & (1 << 1)) << 2) ^ (baseRand & (1 << 3)) | (baseRand >> 1));
		}
		_num = binToNum(_bin);
		if (Check_miller(_num, k))
		{
			prime->push_back(_num);
			return;
		}
		cout << ".";
	}
}