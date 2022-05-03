#include "Knight.h"

Knight::Knight(int n, char t)
{
	name = n;
	dest = -1;
	type = t;
	pos = n;
	finished = false;
	posatroute = 0;

}
