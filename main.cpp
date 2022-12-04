#include "library.h"

int main()
{
	int bits;
	cout << "Enter the number of bits: ";
	cin >> bits;
	bits /= 2;
	cout << "generating prime number:\n";
	vector<X> *primes = new vector<X>();
	for (int i = 0; i < 2; i++)
	{
		thread t(generateBigPrime, 2, bits, primes, i + 1);
		t.detach();
	}
	while (primes->size() < 2)
		;
	cout << "Done\n\n";
	X p = primes[0][0], q = primes[0][1];
	cout << "Keys generated\n";
	X n = p * q;
	X phi = (p - 1) * (q - 1);
	X e = 65537;
	X d = inverse(e, phi);
	cout << "n = " << n.get_value() << endl;
	cout << "e = " << e.get_value() << endl;
	cout << "d = " << d.get_value() << endl;
}
// int main()
// {
// 	X p = 13;
// 	if (Check_miller(p,1))
// 		cout << "true";
// 	else
// 		cout << "false";
// 	X p = 4, q = 13;
// 	cout<<(p%q).get_value();
// }