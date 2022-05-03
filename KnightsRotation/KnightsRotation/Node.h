#pragma once
#include <vector>
using namespace std;

class Node
{
public:
	int name;
	vector<Node*> children;
	Node* parent;
	Node(int n, Node* p);
};

