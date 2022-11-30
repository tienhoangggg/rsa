#include <iostream>
#include<string>
#include <tuple>
using namespace std;
typedef unsigned long long X;

bool test(X a, X b, X c, X w) {
    if (c == w) return true;
    X p = pow(w, b, c);
    if (p == 1) return true;
    for (; a > 0; a--) {
        if (p == c - 1) return true;
        p = p * p % c;
    }
    return false;
}

X pow(X j, X k, X l) {
    X result = 1;
    j = j % l;
    while (k > 0) {
        if (k & 1) result = result * j % l;
        k >>= 1;
        j = j * j % l;
    }
    return result;
}
bool Check_miller(X n) {
    if (n < 2) return false;
    if ((n & 1) == 0) return n == 2;
    X s,d;
    tie(s, d) = factor(n - 1);
    return test(s, d, n, 2) && test(s, d, n, 3);
}

pair<X, X> factor(X n) {
    X s = 0;
    while ((n & 1) == 0) {
        s++;
        n >>= 1;
    }
    return { s, n };
}

int main() {
    cout << Check_miller(21);
}