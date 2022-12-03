#include "library.h"

X inverse(X a, X b)
{
	X x = 0, y = 1, x2 = 1, y2 = 0, x3, y3, bb = b;
	while (a > 1)
	{
		X q = b / a, r = b - q * a;
		x3 = x - x2 * q;
		y3 = y - y2 * q;
		b = a, a = r;
		x = x2, y = y2;
		x2 = x3, y2 = y3;
	}
	while (x2.get_value()[0] == '-')
		x2 = bb - x2.get_value().substr(1);
	return x2;
}