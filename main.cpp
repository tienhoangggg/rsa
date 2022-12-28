#include "library.h"
#include "genePrime.cpp"
#include "bigNum.cpp"
#include "find_d.cpp"

vector<X> generateKey(int bits)
{
	bits /= 2;
	cout << "RSA key - " << bits * 2 << endl;
	cout << "generating prime number " << bits << ": \n";

	vector<X> *primes = new vector<X>();
	for (int i = 0; i < 8; i++)
	{
		thread t(generateBigPrime, 5, bits, primes, i + 1);
		t.detach();
	}
flag:;
	vector<X> res;
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
		res.push_back(n);
		res.push_back(e);
		res.push_back(d);
		cout << "Done\n\nKeys generated\nn = " << n.get_value() << "\ne = " << e.get_value() << "\nd = " << d.get_value() << endl;
	}
	catch (const std::exception &e)
	{
		goto flag;
	}
	return res;
}

int main()
{
	int bits;
	vector<X> key;
	X n, e, d;

	while (1)
	{
		cout << "+========== RSA KEY =========+" << endl;
		cout << "| 1. Generate key            |" << endl;
		cout << "| 2. Input key               |" << endl;
		cout << "| 0. Exit                    |" << endl;
		cout << "+============================+" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter bits: ";
			cin >> bits;
			bits = ((bits - 1) / 8 + 1) * 8;
			key = generateKey(bits);
			n = key[0];
			e = key[1];
			d = key[2];
		}
		else if (choice == 2)
		{
			string temp;
			cout << "Enter n: ";
			cin >> temp;
			n = X(temp);
			cout << "Enter e: ";
			cin >> temp;
			e = X(temp);
			cout << "Enter d: ";
			cin >> temp;
			d = X(temp);
		}
		else
		{
			break;
		}
		while (1)
		{
			cout << "+====== Encrypt/Decrypt =====+" << endl;
			cout << "| 1. Encrypt                 |" << endl;
			cout << "| 2. Decrypt                 |" << endl;
			cout << "| 0. Exit                    |" << endl;
			cout << "+============================+" << endl;
			int _choice;
			cin >> _choice;
			string inAdr, outAdr, tmp;
			X mess;
			char c;
			ifstream in;
			ofstream out;
			int bytes = bits / 8;
			if (_choice == 1)
			{
				cout << "Enter the path to your plaintext file: ";
				cin >> inAdr;
				cout << "Enter the path to your cypher file: ";
				cin >> outAdr;
				in.open(inAdr);
				out.open(outAdr);
				while (!in.eof())
				{
					mess = 0;
					for (int i = 0; i < bytes; i++)
					{
						c = in.get();
						if (c == EOF)
							c = '\n';
						mess = mess * 256 + int(c);
					}
					mess = pow(mess, e, n);
					out << mess.get_value() << endl;
				}
				in.close();
				out.close();
			}
			else if (_choice == 2)
			{
				cout << "Enter the path to your cypher file: ";
				cin >> inAdr;
				cout << "Enter the path to your plaintext file: ";
				cin >> outAdr;
				in.open(inAdr);
				out.open(outAdr);
				while (!in.eof())
				{
					getline(in, tmp);
					mess = X(tmp);
					mess = pow(mess, d, n);
					tmp = "";
					while (mess > 0)
					{
						tmp = char(strtol((mess % 256).get_value().c_str(), NULL, 10)) + tmp;
						mess = mess / 256;
					}
					out << tmp;
				}
				in.close();
				out.close();
			}
			else
			{
				break;
			}
		}
	}
	return 0;
}
