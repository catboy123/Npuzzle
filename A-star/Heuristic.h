#pragma once
#include<iostream>
#include<math.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
typedef pair<int, int> ii;

class Heuristic {
public:
	Heuristic() {}
	virtual  int calc(int n, int** A, int** B) {
		return 0;
	}
};
class Euclide :public Heuristic {
public:
	int calc(int n, int** A, int** B);
};//*/
class Manhattan :public Heuristic {
public:
	int calc(int n, int** A, int** B);
};//*/
class MisplacedTiles :public Heuristic {
public:
	int calc(int n, int** A, int** B);
};//*/
class LinearConflict :public Heuristic {
public:
	int calc(int n, int** A, int** B);
};//*/
class Gaschnig :public Heuristic {
public:
	int calc(int n, int** A, int** B);
};//*/
