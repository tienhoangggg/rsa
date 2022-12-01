#include "library.h"

class number;

number::number(string val)
{
    value = val;    
}

number::number(int val)
{
    value = to_string(val);
}

string number::get_value()
{
    return value;
}

bool number::operator < (number num)
{
    if(value.length() < num.get_value().length())
        return true;
    else if(value.length() > num.get_value().length())
        return false;
    else
    {
        for(int i = 0; i < value.length(); i++)
        {
            if(value[i] < num.get_value()[i])
                return true;
            else if(value[i] > num.get_value()[i])
                return false;
        }
    }
    return false;
}

bool number::operator > (number num)
{
    if(value.length() > num.get_value().length())
        return true;
    else if(value.length() < num.get_value().length())
        return false;
    else
    {
        for(int i = 0; i < value.length(); i++)
        {
            if(value[i] > num.get_value()[i])
                return true;
            else if(value[i] < num.get_value()[i])
                return false;
        }
    }
    return false;
}

bool number::operator <= (number num)
{
    if(value.length() < num.get_value().length())
        return true;
    else if(value.length() > num.get_value().length())
        return false;
    else
    {
        for(int i = 0; i < value.length(); i++)
        {
            if(value[i] < num.get_value()[i])
                return true;
            else if(value[i] > num.get_value()[i])
                return false;
        }
    }
    return true;
}

bool number::operator == (number num)
{
    if(value.length() != num.get_value().length())
        return false;
    else
    {
        for(int i = 0; i < value.length(); i++)
        {
            if(value[i] != num.get_value()[i])
                return false;
        }
    }
    return true;
}

number number::operator = (number num)
{
    value = num.get_value();
    return *this;
}

number number:: operator+(number val)
{
    number result;
    string a = this->value;
    string b = val.value;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    while (i >= 0 || j >= 0)
    {
        int sum = carry;
        if (i >= 0)
            sum += a[i] - '0';
        if (j >= 0)
            sum += b[j] - '0';
        result.value = to_string(sum % 10) + result.value;
        carry = sum / 10;
        i--;
        j--;
    }
    if (carry)
        result.value = to_string(carry) + result.value;
    return result;
}

number  number:: operator-(number val)
{
    number result;
    string a = this->value;
    string b = val.value;
    int carry = 0;
    int i = a.length() - 1;
    int j = b.length() - 1;
    while (i >= 0 || j >= 0)
    {
        int minus = carry;
        if (i >= 0)
            minus += a[i] - '0';
        if (j >= 0)
            minus -= b[j] - '0';
        if (minus < 0)
        {
            minus += 10;
            carry = -1;
        }
        else
            carry = 0;
        result.value = to_string(minus) + result.value;
        i--;
        j--;
    }
    i = 0;
    while (result.value[i] == '0')
        i++;
    result.value = result.value.substr(i);
    if (result.value.empty())
        result.value = "0";
    return result;
}

number number:: operator*(number val)
{
    if (this->value == "0" || val.value == "0")
        return number("0");
    number result;
    string a = this->value;
    string b = val.value;
    int carry = 0;
    int n = a.length() - 1;
    int m = b.length() - 1;
    vector<int> temp(n+m+2, 0);
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            temp[i + j] += (a[i] - '0') * (b[j] - '0');
        }
    }
    for (int i = n + m; i > 0; i--)
    {
        temp[i - 1] += temp[i] / 10;
        temp[i] %= 10;
    }
    for (int i = 0; i <= n + m; i++)
    {
        result.value += to_string(temp[i]);
    }
    return result;
}

number number:: operator/(number val)
{
    number result("0");
    string a = this->value;
    if (a == "0" || val.value == "0" || *this < val)
        return result;
    int n = a.length();
    int m = val.value.length();
    int carry = 0;
    int i,j,k;
    for (i = 0; (result*10 + (a[i]-'0')) < val; i++)
    {
        result = result * 10 + (a[i]-'0');
    }
    vector<int> v(n, 0);
    for (j = i; j < n; j++)
    {
        result = result * 10 + (a[j]-'0');
        for (k = 0; val <= result; k++)
        {
            result = result - val;
        }
        v[j] = k;
    }
    result.value = "";
    for (int j = i; j < n; j++)
    {
        result.value += to_string(v[j]);
    }
    return result;
}

number number:: operator%(number val)
{
    number result("0");
    string a = this->value;
    if (a == "0" || val.value == "0")
        return result;
    int n = a.length();
    int m = val.value.length();
    int carry = 0;
    int i, j, k;
    for (i = 0; (result * 10 + (a[i] - '0')) < val; i++)
    {
        result = result * 10 + (a[i] - '0');
    }
    for (j = i; j < n; j++)
    {
        result = result * 10 + (a[j] - '0');
        for (k = 0; val <= result; k++)
        {
            result = result - val;
        }
    }
    return result;
}