#include "library.h"

int main()
{
    srand(time(NULL));
    int bits;
    cout<<"Enter the number of bits: ";
    cin>>bits;
    cout<<"generating prime number:\nP";
    X p = generateBigPrime(2, bits);
    cout<<"\nQ";
    X q = generateBigPrime(2, bits);
    cout<<"\nKeys generated\n";
    X n = p * q;
    X phi = (p - 1) * (q - 1);
    X e = 65537;
    X d = inverse(e, phi);
    cout<<"n = "<<n.get_value()<<endl;
    cout<<"e = "<<e.get_value()<<endl;
    cout<<"d = "<<d.get_value()<<endl;
}