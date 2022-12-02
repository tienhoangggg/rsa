#include "library.h"
#include <time.h>
#include <random>
typedef number X;

X pow(X a, X b, X n)
{
    X result = 1;
    while (b > 0)
    {
        if (!b.mod2())
            result = result * a % n;
        b = b / 2;
        a = a * a % n;
    }
    return result;
}

bool test(int s, X m, X n, X a)
{
    if (n == a)
        return true;
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
        X a = X(rand()) % (1) + 2;
        if (!test(s, d, n, a))
            return false;
    }
    return true;
}

vector<int> randomOddNum(int bits)
{
    vector<int> _bin(bits, 0);
    _bin[0] = 1;
    _bin[bits - 1] = 1;
    for (int i = 1; i < bits - 1; ++i)
    {
        _bin[i] = rand() % 2;
    }
    return _bin;
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

X generateBigPrime(int k, int bits)
{
    vector<int> _bin;
    while (1)
    {
        _bin = randomOddNum(bits);
        X _num = binToNum(_bin);
        cout<<".";
        if (Check_miller(_num, k))
        {
            return _num;
        }
    }
}