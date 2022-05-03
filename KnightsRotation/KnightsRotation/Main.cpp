#include <stdlib.h>
#include "Knight.h"
#include "Node.h"
#include "Globals.h"
using namespace std;

Knight* board[12];
Node* map[12];
int bd[3];
int wd[3];

void initialize();

int main() {

	return 0;
}

void initialize() {

	//initializing board
	board[0] = new Knight(0, 'b');
	board[1] = new Knight(1, 'b');
	board[2] = new Knight(2, 'b');
	board[3] = nullptr;
	board[4] = nullptr;
	board[5] = nullptr;
	board[6] = nullptr;
	board[7] = nullptr;
	board[8] = nullptr;
	board[9] = new Knight(9, 'w');
	board[10] = new Knight(10, 'w');
	board[11] = new Knight(11, 'w');

	//initializing map which contains available moves for each tile
	map[0] = new Node(0, nullptr);
	map[0]->children.push_back(new Node(5, map[0]));
	map[0]->children.push_back(new Node(7, map[0]));
	map[1] = new Node(1, nullptr);
	map[1]->children.push_back(new Node(6, map[1]));
	map[1]->children.push_back(new Node(8, map[1]));
	map[2] = new Node(2, nullptr);
	map[2]->children.push_back(new Node(3, map[2]));
	map[2]->children.push_back(new Node(7, map[2]));
	map[3] = new Node(3, nullptr);
	map[3]->children.push_back(new Node(2, map[3]));
	map[3]->children.push_back(new Node(8, map[3]));
	map[3]->children.push_back(new Node(10, map[3]));
	map[4] = new Node(4, nullptr);
	map[4]->children.push_back(new Node(9, map[4]));
	map[4]->children.push_back(new Node(11, map[4]));
	map[5] = new Node(5, nullptr);
	map[5]->children.push_back(new Node(0, map[5]));
	map[5]->children.push_back(new Node(6, map[5]));
	map[5]->children.push_back(new Node(10, map[5]));
	map[6] = new Node(6, nullptr);
	map[6]->children.push_back(new Node(1, map[6]));
	map[6]->children.push_back(new Node(5, map[6]));
	map[6]->children.push_back(new Node(11, map[6]));
	map[7] = new Node(7, nullptr);
	map[7]->children.push_back(new Node(0, map[7]));
	map[7]->children.push_back(new Node(2, map[7]));
	map[8] = new Node(8, nullptr);
	map[8]->children.push_back(new Node(1, map[8]));
	map[8]->children.push_back(new Node(3, map[8]));
	map[8]->children.push_back(new Node(9, map[8]));
	map[9] = new Node(9, nullptr);
	map[9]->children.push_back(new Node(4, map[9]));
	map[9]->children.push_back(new Node(8, map[9]));
	map[10] = new Node(10, nullptr);
	map[10]->children.push_back(new Node(3, map[10]));
	map[10]->children.push_back(new Node(5, map[10]));
	map[11] = new Node(11, nullptr);
	map[11]->children.push_back(new Node(4, map[11]));
	map[11]->children.push_back(new Node(6, map[11]));

	//initializing destinations for both factions
	bd[0] = 9;
	bd[1] = 10;
	bd[2] = 11;
	wd[0] = 0;
	wd[1] = 1;
	wd[2] = 2;
}