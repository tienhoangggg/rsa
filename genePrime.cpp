#include "library.h"
#include <time.h>
#include <random>
typedef number X;

X pow(X a, X b, X n)
{
    X result = 1;
    a = a % n;
    while (b > 0)
    {
        if (!b.mod2())
            result = result * a % n;
        b = b / 2;
        a = a * a % n;
    }
    return result;
}

bool test(X s, X m, X n, X a)
{
    if (n == a)
        return true;
    X p = pow(a, m, n);
    if (p == 1)
        return true;
    for (; s > 0; s = s - 1)
    {
        if (p == n - 1)
            return true;
        p = p * p % n;
    }
    return false;
}

bool Check_miller(X n, int k)
{
    if (n < 2)
        return false;
    if (n.mod2())
        return n == 2;
    X s = 0, d = n - 1;
    while (d.mod2())
    {
        s = s + 1;
        d = d / 2;
    }
    while(k--)
    {
        X a = X (rand()) % (n - 2) + 2;
        if (!test(s, d, n, a))
            return false;
    }
    return true;
}

vector<int> randomOddNum(int bits){
    srand(time(NULL));
    vector<int> _bin(bits, 0);
    _bin[0] = 1;
    _bin[bits - 1] = 1;
    for (int i = 1; i < bits - 1; ++i){
        _bin[i] = rand() % 2;
    }
    return _bin;
}

X binToNum(vector<int> num){
    X n = 0, pow_2 = 1;
    for(int i = num.size() - 1; i >= 0; --i){
        n = n + (pow_2 * num[i]);
        pow_2 = pow_2 * 2;
    }
    return n;
}

X generateBigPrime(int k, int bits){
    vector<int> _bin;
    X _num;
    while(1){
        _bin = randomOddNum(bits);
        _num = binToNum(_bin);
        if (Check_miller(_num, k))
            break;
    }
    return _num;
}
