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
        if (b % 2 == 1)
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
    if (n % 2 == 0)
        return n == 2;
    X s = 0, d = n - 1;
    while (d % 2 == 0)
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