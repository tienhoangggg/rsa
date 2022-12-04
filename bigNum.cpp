#include "library.h"

class number;

number::number(int val)
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

number::number(vector<int> val, bool sign = true)
{
	value = val;
	sign = sign;
}

void number::handle()
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
		// if (i != 0)
		// {
		// 	int temp = value[i];
		// 	int count = 0;
		// 	while (temp > 0)
		// 	{
		// 		temp /= 10;
		// 		count++;
		// 	}
		// 	for (int j = 0; j < 4 - count; j++)
		// 		s += "0";
		// }
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
	return *this;
}

number number::operator+(number val)
{
	number result;
	vector<int> a = this->value;
	vector<int> b = val.value;
	int carry = 0;
	int i = a.size() - 1;
	int j = b.size() - 1;
	while (i >= 0 || j >= 0)
	{
		int sum = carry;
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
	vector<int> a = this->value;
	vector<int> b = val.value;
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
		int minus = carry;
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
	result.handle();
	return result;
}

number number::operator*(number val)
{
	number result;
	vector<int> a = this->value;
	vector<int> b = val.value;
	if ((this->sign == false && val.sign != false) || (this->sign != false && val.sign == false))
		result.sign = false;
	int carry = 0;
	int n = a.size();
	int m = b.size();
	vector<int> temp(n + m, 0);
	for (int i = 1; i <= n; i++)
	{
		int temp1 = a[i - 1];
		for (int j = 1; j <= m; j++)
		{
			temp[i + j - 1] += temp1 * b[j - 1];
		}
	}
	for (int i = n + m - 1; i > 0; i--)
	{
		temp[i - 1] += temp[i] / base;
		temp[i] %= base;
	}
	result.value = temp;
	result.handle();
	return result;
}

number number::operator/(number val)
{
	number result;
	vector<int> a = this->value;
	if (*this == 0 || val == 0 || *this < val)
		return result;
	int n = a.size();
	int i, j, k;
	for (i = 0; result < val; i++)
	{
		result.value.push_back(a[i]);
	}
	i--;
	result.value.pop_back();
	vector<int> v(n, 0);
	for (j = i; j < n; j++)
	{
		result.handle();
		result.value.push_back(a[j]);
		for (k = 0; val <= result; k++)
		{
			result = result - val;
		}
		v[j] = k;
	}
	result.value = v;
	result.handle();
	return result;
}

number number::operator%(number val)
{
	number result;
	vector<int> a = this->value;
	if (*this == 0 || val == 0)
		return result;
	if (*this < val)
		return *this;
	int n = a.size();
	int i, j, k;
	for (i = 0; result < val; i++)
	{
		result.value.push_back(a[i]);
	}
	result.value.pop_back();
	i--;
	for (j = i; j < n; j++)
	{
		result.handle();
		result.value.push_back(a[j]);
		for (k = 0; val <= result; k++)
		{
			result = result - val;
		}
	}
	result.handle();
	return result;
}