#include <stdlib.h>
#include <iostream>
#include <queue>
#include "Knight.h"
#include "Node.h"
using namespace std;

#define DESTNO 3
#define TILENO 12

//globals
Knight* board[TILENO];
Node* map[TILENO];
int bd[DESTNO];
int wd[DESTNO];
Knight* last;
int moves = 0;

//functions
void initialize();
void move(Knight* to, Knight* from);
void shortestRoute(Knight* kn, int restricted);
void moveToDestination(Knight* kn);
void moveOutOfWay(Knight* kn);
bool collision(Knight* kn1, Knight* kn2);
bool done();
void printBoard();

//main loop
int main() {
	initialize();
	last = board[0];

	while (!done() && !last->finished) {
		move(last, nullptr);
	}

	int index = 0;
	while (!done()) {
		if (board[index] != nullptr) {
			if (!board[index]->finished) {
				move(board[index], nullptr);
			}
		}
		index++;
	}

	cout << "Number of moves is: " << moves << endl;
	system("pause");
	return 0;
}

//initialization function
void initialize() {

	//initializing board
	board[0] = new Knight(0, 'B');
	board[1] = new Knight(1, 'B');
	board[2] = new Knight(2, 'B');
	board[3] = nullptr;
	board[4] = nullptr;
	board[5] = nullptr;
	board[6] = nullptr;
	board[7] = nullptr;
	board[8] = nullptr;
	board[9] = new Knight(9, 'W');
	board[10] = new Knight(10, 'W');
	board[11] = new Knight(11, 'W');

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

//main problem solving function
//commands a knight to move
//order usually given "from" a knight "to" a knight
void move(Knight* to, Knight* from)
{
	//determines shortest route for the "to" knight
	if (to->finished) return;
	if (to->dest == -1) {
		if (from == nullptr) {
			shortestRoute(to, -1);
		}
		else {
			shortestRoute(to, from->name);
		}
	}
	//determines if destination is occupied
	Knight* obstacle = board[to->dest];
	if (obstacle != nullptr) {
		if (obstacle->dest == -1) {
			shortestRoute(obstacle, to->name);
		}
		//determines if collision will occur, and solves it
		if (collision(to, obstacle)) {
			Knight* moved;
			if (to->route.size() > obstacle->route.size()) {
				moved = to;
				moveOutOfWay(to);
			}
			else {
				moved = obstacle;
				moveOutOfWay(obstacle);
			}
			last = moved;
			if (board[to->dest] == nullptr) {
				moveToDestination(to);
				return;
			}
		}
		//commands occupying knight to move
		move(obstacle, to);
	}
	//moves to destination after all obstacles and collisions have been resolved
	moveToDestination(to);
	return;
}

//determines shortest route for a given knight
void shortestRoute(Knight* kn, int restricted)
{
	Node* cn = new Node(kn->name, nullptr);
	queue<Node*> q;
	bool found = false;
	Node* jackpot = cn;
	vector<int> dest;

	//determines destinations that can be taken
	if (kn->type == 'B') {
		for (int i = 0; i < DESTNO; i++) {
			if (bd[i] != restricted && bd[i] != -1) {
				dest.push_back(bd[i]);
			}
		}
	}
	else {
		for (int i = 0; i < DESTNO; i++) {
			if (wd[i] != restricted && wd[i] != -1) {
				dest.push_back(wd[i]);
			}
		}
	}

	//tries to find chosen destination while trying all routes to choose shortest route
	while (!found) {
		vector<Node*> roads = map[cn->name]->children;
		for (int x = 0; x < roads.size(); x++) {
			Node* nn = new Node(roads[x]->name, cn);
			cn->children.push_back(nn);
			for (int y = 0; y < dest.size(); y++) {
				if (nn->name == dest[y]) {
					found = true;
					jackpot = nn;
					break;
				}
			}
			q.push(nn);
		}
		cn = q.front();
		q.pop();
	}

	//extracts and stores proper information about route and destination in knight's attributes
	vector<int> route;
	kn->dest = jackpot->name;
	while (jackpot != nullptr) {
		route.insert(route.begin(), jackpot->name);
		jackpot = jackpot->parent;
	}
	kn->route = route;
	if (kn->type == 'B') {
		for (int in = 0; in < DESTNO; in++) {
			if (bd[in] == kn->dest) bd[in] = -1;
		}
	}
	else {
		for (int in = 0; in < DESTNO; in++) {
			if (wd[in] == kn->dest) wd[in] = -1;
		}
	}
}

//safely moves knight to chosen destination
void moveToDestination(Knight* kn)
{
	while (kn->routeIndex + 1 < kn->route.size()) {
		int nextStep = kn->route[kn->routeIndex + 1];
		if (board[nextStep] != nullptr) return;
		else {
			board[nextStep] = kn;
			board[kn->pos] = nullptr;
			kn->routeIndex++;
			kn->pos = nextStep;
			moves++;
			printBoard();
		}
	}
	kn->finished = true;
	return;
}

//moves knight out of way in case of collision
void moveOutOfWay(Knight* kn)
{
	int nextStep = kn->route[kn->routeIndex + 1];
	if (board[nextStep] != nullptr) {
		nextStep = kn->route[kn->routeIndex - 1];
		board[nextStep] = kn;
		board[kn->pos] = nullptr;
		kn->routeIndex--;
		kn->pos = nextStep;
		moves++;
		printBoard();
	}
	else {
		moveToDestination(kn);
	}
	return;
}

//checks for collisions in two given knights' routes
bool collision(Knight* kn1, Knight* kn2)
{
	int commonNodes = 0;
	for (int x = 0; x < kn1->route.size(); x++) {
		for (int y = 0; y < kn2->route.size(); y++) {
			if (kn1->route[x] == kn2->route[y]) {
				commonNodes++;
			}
		}
	}
	if (commonNodes > 1) return true;
	else return false;
}

//checks whether all knights have reached their destinations or not
bool done()
{
	for (int i = 0; i < TILENO; i++) {
		if (board[i] == nullptr) continue;
		else {
			if (!board[i]->finished) return false;
		}
	}
	return true;
}

//prints current board layout
void printBoard()
{
	cout << "Move number " << moves << endl;
	for (int i = 0; i < TILENO; i++) {
		if (board[i] == nullptr) {
			cout << "0\t";
		}
		else {
			cout << board[i]->type << "\t";
		}
		if (i % 3 == 2)cout << endl << endl;
	}
	cout << endl;
	system("pause");
}
