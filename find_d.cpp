#include "library.h"

X inverse(X a, X b)
{
	X x = 1, y = 0, x2 = 0, y2 = 1, x3, y3, bb = b;
	while (a > 1)
	{
		X q = b / a, r = b - q * a;
		x3 = x - x2 * q;
		y3 = y - y2 * q;
		b = a, a = r;
		x = x2, y = y2;
		x2 = x3, y2 = y3;
	}
	while (y2.sign == false)
	{
		y2.sign = true;
		y2 = bb - y2;
	}
	return y2;
}