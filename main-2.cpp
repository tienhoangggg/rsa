#include "library.h"
#include "genePrime.cpp"
#include "bigNum.cpp"
#include "find_d.cpp"



int main()
{
	int bits;
	cin >> bits;
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
    X p, q, n, phi, e, d;
	while (primes->size() < 2);
	try
	{
	    p = primes->at(0);
		q = primes->at(1);
		n = p * q;
		phi = (p - 1) * (q - 1);
		e = 65537;
		d = inverse(e, phi);

		cout << "Done\n\nKeys generated\nn = " << n.get_value() << "\ne = " << e.get_value() << "\nd = " << d.get_value() << endl;
	}
	catch (const std::exception &e)
	{
		goto flag;
	}

    while(1){
        int a;
        cout << "enter: ";
        cin >> a;

        if(a == 1){
            fstream f;
            string pl;
            f.open("plain-text.txt", ios::in);
            while(!f.eof()){
            getline(f, pl);
            }
            f.close();

            cout << endl;
            f.open("cypher-text.txt", ios::out);
            for(auto& c : pl){
                X r = pow(X(c), e, n);
                cout << r.get_value() << endl;
                
                f << r.get_value() << endl;
            }
            f.close();
        }
        else{
            string l;
            fstream out, in;
            out.open("plain-text.txt", ios::out | ios::app);
            in.open("cypher-text.txt", ios::in);
            while(!in.eof()){
                getline(in, l);
                if (l == ""){
                    continue;
                }
                X t(l);
                
                X r = pow(t, d, n);
                cout << r.get_value() << endl;
                
                cout << stoi(r.get_value()) << endl;
                
                out << char(stoi(r.get_value())) << endl;
            }
            out.close();
            in.close();

        }
    }
    
    // string s = "123900000000123456789";
    // X a(s);
    // X b = a + X(1);
    // cout << endl << b.get_value();

	return 0;
}