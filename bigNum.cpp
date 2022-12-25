#include "library.h"

class number;

number::number(long long val)
{
	if (val < 0)
	{
		sign = false;
		val *= -1;
	}
	while (val > 0)
	{
		value.insert(value.begin(), val % base);
		val /= base;
	}
}

number::number(vector<long long> val, bool sign = true)
{
	value = val;
	sign = sign;
}

number::number(string s){
	int _n = s.length();
	int du = _n % 9;
	value.push_back(stoll(s.substr(0, du)));
    	for(int i = du; i < _n; i += 9){
        	value.push_back(stoll(s.substr(i, 9)));
    	}
}

void number::fix()
{
	while (!value.empty() && value[0] == 0)
		value.erase(value.begin());
}

string number::get_value()
{
	string s = "";
	if (!sign)
		s += "-";
	for (int i = 0; i < value.size(); i++)
	{
		if (i != 0)
		{
			long long temp = value[i];
			int count = 0;
			while (temp > 0)
			{
				temp /= 10;
				count++;
			}
			for (int j = 0; j < 9 - count; j++)
				s += "0";
		}
		s += to_string(value[i]);
	}
	if (s == "")
		s = "0";
	return s;
}

bool number::operator<(number num)
{
	if (value.size() < num.value.size())
		return true;
	else if (value.size() > num.value.size())
		return false;
	else
	{
		for (int i = 0; i < value.size(); i++)
		{
			if (value[i] < num.value[i])
				return true;
			else if (value[i] > num.value[i])
				return false;
		}
	}
	return false;
}

bool number::operator>(number num)
{
	if (value.size() > num.value.size())
		return true;
	else if (value.size() < num.value.size())
		return false;
	else
	{
		for (int i = 0; i < value.size(); i++)
		{
			if (value[i] > num.value[i])
				return true;
			else if (value[i] < num.value[i])
				return false;
		}
	}
	return false;
}

bool number::operator<=(number num)
{
	if (value.size() < num.value.size())
		return true;
	else if (value.size() > num.value.size())
		return false;
	else
	{
		for (int i = 0; i < value.size(); i++)
		{
			if (value[i] < num.value[i])
				return true;
			else if (value[i] > num.value[i])
				return false;
		}
	}
	return true;
}

bool number::operator==(number num)
{
	if (value.size() != num.value.size())
		return false;
	else
	{
		for (int i = 0; i < value.size(); i++)
		{
			if (value[i] != num.value[i])
				return false;
		}
	}
	return true;
}

bool number::mod2()
{
	if (value[value.size() - 1] % 2 == 0)
		return true;
	else
		return false;
}

number number::operator=(number num)
{
	value = num.value;
	sign = num.sign;
	return *this;
}

number number::operator+(number val)
{
	number result;
	vector<long long> a = this->value;
	vector<long long> b = val.value;
	int carry = 0;
	int i = a.size() - 1;
	int j = b.size() - 1;
	while (i >= 0 || j >= 0)
	{
		long long sum = carry;
		if (i >= 0)
			sum += a[i];
		if (j >= 0)
			sum += b[j];
		result.value.insert(result.value.begin(), sum % base);
		carry = sum / base;
		i--;
		j--;
	}
	if (carry)
		result.value.insert(result.value.begin(), carry);
	return result;
}

number number::operator-(number val)
{
	number result;
	vector<long long> a = this->value;
	vector<long long> b = val.value;
	if (this->sign == false && val.sign != false)
	{
		result = number(a) + number(b);
		result.sign = false;
		return result;
	}
	else if (this->sign != false && val.sign == false)
	{
		result = number(a) + number(b);
		return result;
	}
	else if (this->sign == false && val.sign == false)
	{
		result = number(b) - number(a);
		return result;
	}
	if (*this < val)
	{
		result = number(b) - number(a);
		result.sign = false;
		return result;
	}
	int carry = 0;
	int i = a.size() - 1;
	int j = b.size() - 1;
	while (i >= 0 || j >= 0)
	{
		long long minus = carry;
		if (i >= 0)
			minus += a[i];
		if (j >= 0)
			minus -= b[j];
		if (minus < 0)
		{
			minus += base;
			carry = -1;
		}
		else
			carry = 0;
		result.value.insert(result.value.begin(), minus);
		i--;
		j--;
	}
	result.fix();
	return result;
}

number number::operator*(number val)
{
	number result;
	vector<long long> a = this->value;
	vector<long long> b = val.value;
	if ((this->sign == false && val.sign != false) || (this->sign != false && val.sign == false))
		result.sign = false;
	int n = a.size();
	int m = b.size();
	vector<long long> temp(n + m, 0);
	for (int i = n; i > 0; i--)
	{
		long long temp1 = a[i - 1];
		for (int j = m; j > 0; j--)
		{
			temp[i + j - 1] += temp1 * b[j - 1];
			temp[i + j - 2] += temp[i + j - 1] / base;
			temp[i + j - 1] %= base;
		}
	}
	result.value = temp;
	result.fix();
	return result;
}

number number::operator/(number val)
{
	number result;
	vector<long long> a = this->value;
	if (*this == 0 || val == 0 || *this < val)
		return result;
	int n = a.size();
	int i, j;
	for (i = 0; result < val; i++)
	{
		result.value.push_back(a[i]);
	}
	i--;
	result.value.pop_back();
	vector<long long> v(n, 0);
	for (j = i; j < n; j++)
	{
		result.value.push_back(a[j]);
		if (result < val)
		{
			v[j] = 0;
		}
		else
		{
			long long k, l = 0, r = base;
			number temp, temp1;
			temp1 = result - val;
			while (l <= r)
			{
				k = (r - l) / 2 + l;
				temp = val * k;
				if (temp <= temp1)
				{
					l = k + 1;
				}
				else if (temp > result)
				{
					r = k - 1;
				}
				else
				{
					v[j] = k;
					result = result - temp;
					break;
				}
			}
		}
	}
	result.value = v;
	result.fix();
	return result;
}

number number::operator%(number val)
{
	number result;
	vector<long long> a = this->value;
	if (*this == 0 || val == 0)
		return result;
	if (*this < val)
		return *this;
	int n = a.size();
	int i, j;
	for (i = 0; result < val; i++)
	{
		result.value.push_back(a[i]);
	}
	result.value.pop_back();
	i--;
	for (j = i; j < n; j++)
	{
		result.value.push_back(a[j]);
		if (!(result < val))
		{
			long long k, l = 0, r = base;
			number temp, temp1;
			temp1 = result - val;
			while (l <= r)
			{
				k = (r - l) / 2 + l;
				temp = val * k;
				if (temp <= temp1)
				{
					l = k + 1;
				}
				else if (temp > result)
				{
					r = k - 1;
				}
				else
				{
					result = result - temp;
					break;
				}
			}
		}
	}
	result.fix();
	return result;
}
