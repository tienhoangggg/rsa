#include "library.h"

int main()
{
	int bits;
	cout << "Enter the number of bits: ";
	cin >> bits;
	bits /= 2;
	cout << "generating prime number:\n";
	vector<X> *primes = new vector<X>();
	for (int i = 0; i < 8; i++)
	{
		thread t(generateBigPrime, 2, bits, primes, i + 1);
		t.detach();
	}
flag:;
	while (primes->size() < 2)
		;
	try
	{
		X p = primes->at(0);
		X q = primes->at(1);
		X n = p * q;
		X phi = (p - 1) * (q - 1);
		X e = 65537;
		X d = inverse(e, phi);
		cout << "Done\n\nKeys generated\nn = " << n.get_value() << "\ne = " << e.get_value() << "\nd = " << d.get_value();
	}
	catch (const std::exception &e)
	{
		goto flag;
	}
}