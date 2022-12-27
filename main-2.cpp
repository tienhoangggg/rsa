#include "library.h"
#include "genePrime.cpp"
#include "bigNum.cpp"
#include "find_d.cpp"

vector<X> generateKey(int bits){
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
    vector<X> res(3);
	while (primes->size() < 2);
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
    vector<X> key(3);
    X n, e, d;

    while(1){
        cout << "+========== RSA KEY =========+" << endl;
        cout << "| 1. Generate key            |" << endl;
        cout << "| 2. Input key               |" << endl;
        cout << "| 0. Exit                    |" << endl;
        cout << "+============================+" << endl;
        int choice;
        cin >> choice;
        if(choice == 1){
            cout << "Enter bits: ";
            cin >> bits;
            key = generateKey(bits);
            for(auto i : key){
                cout << i.get_value() << endl;
            }
            cout << key[0].get_value() << endl;
            cout << key[1].get_value() << endl;
            cout << key[2].get_value() << endl;

        }
        else if(choice == 2){
        }
        else{
            break;
        }
        while(1){
            cout << "+====== Encrypt/Decrypt =====+" << endl;
            cout << "| 1. Encrypt                 |" << endl;
            cout << "| 2. Decrypt                 |" << endl;
            cout << "| 0. Exit                    |" << endl;
            cout << "+============================+" << endl;

            int _choice;
            cin >> _choice;
            if(_choice == 1){
                string pText, cText, tmp;
                fstream in, out;
                cout << "Enter the path to your plaintext file: ";
                cin >> pText;
                cout << "Enter the path to your cypher file: ";
                cin >> cText;

                in.open(pText, ios::in);
                out.open(cText, ios::out | ios::app);
                while (!in.eof()){
                    getline(in, tmp);
                    for(auto& c:tmp){
                        X re = pow(X(c), e, n);
                        out << re.get_value() << endl;
                    }

                }

            }
            else if(_choice == 2){

            }
            else{
                break;
            }
        }
    }
	return 0;
}
