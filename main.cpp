#include "library.h"

int main()
{
	int bits, choice;
	cout << "+=== RSA KEY GENERATOR ===+" << endl;
	cout << "| 1. 512 bits             |" << endl;
	cout << "| 2. 1024 bits            |" << endl;
	cout << "| 3. 2048 bits            |" << endl;
	cout << "+=========================+" << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	
	choice = 512 * pow(2, choice - 1);
	bits = choice/2;
	cout << "RSA key - " << bits * 2 << endl;
	cout << "generating prime number " << bits << ": \n";
	
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
