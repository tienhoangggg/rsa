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

bool number::operator<(number num)
{
	if (value.length() < num.get_value().length())
		return true;
	else if (value.length() > num.get_value().length())
		return false;
	else
	{
		for (int i = 0; i < value.length(); i++)
		{
			if (value[i] < num.get_value()[i])
				return true;
			else if (value[i] > num.get_value()[i])
				return false;
		}
	}
	return false;
}

bool number::operator>(number num)
{
	if (value.length() > num.get_value().length())
		return true;
	else if (value.length() < num.get_value().length())
		return false;
	else
	{
		for (int i = 0; i < value.length(); i++)
		{
			if (value[i] > num.get_value()[i])
				return true;
			else if (value[i] < num.get_value()[i])
				return false;
		}
	}
	return false;
}

bool number::operator<=(number num)
{
	if (value.length() < num.get_value().length())
		return true;
	else if (value.length() > num.get_value().length())
		return false;
	else
	{
		for (int i = 0; i < value.length(); i++)
		{
			if (value[i] < num.get_value()[i])
				return true;
			else if (value[i] > num.get_value()[i])
				return false;
		}
	}
	return true;
}

bool number::operator==(number num)
{
	if (value.length() != num.get_value().length())
		return false;
	else
	{
		for (int i = 0; i < value.length(); i++)
		{
			if (value[i] != num.get_value()[i])
				return false;
		}
	}
	return true;
}

bool number::mod2()
{
	int r = this->get_value()[this->get_value().length() - 1] - '0';
	if (r % 2 == 0)
		return true;
	else
		return false;
}

number number::operator=(number num)
{
	value = num.get_value();
	return *this;
}

number number::operator+(number val)
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

number number::operator-(number val)
{
	number result;
	string a = this->value;
	string b = val.value;
	if (a[0] == '-' && b[0] != '-')
	{
		a.erase(a.begin());
		result = number(a) + number(b);
		result.value = '-' + result.value;
		return result;
	}
	else if (a[0] != '-' && b[0] == '-')
	{
		b.erase(b.begin());
		result = number(a) + number(b);
		return result;
	}
	else if (a[0] == '-' && b[0] == '-')
	{
		a.erase(a.begin());
		b.erase(b.begin());
		result = number(b) - number(a);
		return result;
	}
	if (*this < val)
	{
		result = number(b) - number(a);
		result.value = '-' + result.value;
		return result;
	}
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

number number::operator*(number val)
{
	if (this->value == "0" || val.value == "0")
		return number("0");
	number result;
	string a = this->value;
	string b = val.value;
	if ((a[0] == '-' && b[0] != '-') || (a[0] != '-' && b[0] == '-'))
		result.value = "-";
	if (a[0] == '-')
		a.erase(a.begin());
	if (b[0] == '-')
		b.erase(b.begin());
	int carry = 0;
	int n = a.length() - 1;
	int m = b.length() - 1;
	vector<int> temp(n + m + 2, 0);
	for (int i = 0; i <= n; i++)
	{
		int temp1 = a[i] - '0';
		for (int j = 0; j <= m; j++)
		{
			temp[i + j] += temp1 * (b[j] - '0');
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

number number::operator/(number val)
{
	number result("0");
	string a = this->value;
	if (a == "0" || val.value == "0" || *this < val)
		return result;
	int n = a.length();
	int i, j, k;
	i = val.get_value().length() - 1;
	number temp;
	temp.value = a.substr(0, i);
	for (i -= 1; temp < val; i++)
	{
		result = temp;
		temp.value += a[i + 1];
	}
	vector<int> v(n, 0);
	for (j = i; j < n; j++)
	{
		if (result.value == "0")
			result.value = a[j];
		else
			result.value += a[j];
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

number number::operator%(number val)
{
	number result("0");
	string a = this->value;
	if (a == "0" || val.value == "0")
		return result;
	if (*this < val)
		return *this;
	int n = a.length();
	int i, j, k;
	i = val.get_value().length() - 1;
	number temp;
	temp.value = a.substr(0, i);
	for (i -= 1; temp < val; i++)
	{
		result = temp;
		temp.value += a[i + 1];
	}
	for (j = i; j < n; j++)
	{
		if (result.value == "0")
			result.value = a[j];
		else
			result.value += a[j];
		for (k = 0; val <= result; k++)
		{
			result = result - val;
		}
	}
	return result;
}