#include "library.h"

class number
{
private:
    string value;
public:
    number();
    ~number();
    number operator + (number);
    number operator - (number);
    number operator * (number);
    number operator / (number);
    number operator % (number);
    number operator << (number);
    number operator >> (number);
    number operator & (number);
};

number::number()
{
}

number::~number()
{
}

number operator+(number a)
{
}

number operator-(number a)
{
}


number operator*(number a)
{
}



number operator&(number a)
{
}

int main()
{
}