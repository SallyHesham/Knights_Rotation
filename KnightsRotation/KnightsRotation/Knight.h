#pragma once
#include <vector>
using namespace std;

class Knight
{
public:
	int name;
	int dest;
	char type;
	vector<int> route;
	bool finished;
	int pos;
	int posatroute;
	Knight(int n, char t);
};

