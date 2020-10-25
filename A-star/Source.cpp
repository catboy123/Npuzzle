#include<iostream>
#include<stdio.h>
#include<map>
#include<queue>
#include<string>
#include<algorithm>
#include<vector>
#include"Heuristic.h"
#include"State.h"
using namespace std;
#define fileinp "Npuzzle.inp"
#define fileout "Npuzzle.out"
#define fi first
#define se second
#define mkp make_pair

//typedef pair<int, int> ii;

const int orientX[] = { 0,0,-1,1 };
const int orientY[] = { -1,1,0,0 };
int step = 0;
int* id;


int State::cnt = 0;
int processing(State sState, State dState);
void inputState(State& sState, State& dState) {
	int n;
	cin >> n;
	sState.set(n, "input");
	dState.set(n, "input");
	n = sqrt(n) + 1;
	int val;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> val;
			sState.set(i, j, val);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> val;
			dState.set(i, j, val);
		}
	}
}
void preprocessing(State& sState,State& dState) {
	int n = sState.getN() * sState.getN();
	int* arr = new int[n];
	id = new int[n];
	for (int i = 0; i < sState.getN(); ++i) {
		for (int j = 0; j < sState.getN(); ++j) {
			arr[i * sState.getN() + j] = sState.get(i,j);
		}
	}
	vector<int> a(arr, arr + n);
	sort(a.begin(), a.end());
	for (int i = 0; i < sState.getN(); ++i) {
		for (int j = 0; j < sState.getN(); ++j) {
			int index = lower_bound(a.begin(), a.end(), sState.get(i,j))-a.begin();
			id[index]=sState.get(i,j);
			sState.set(i, j, index);
		}
	}
	for (int i = 0; i < sState.getN(); ++i) {
		for (int j = 0; j < sState.getN(); ++j) {
			int index = lower_bound(a.begin(), a.end(), dState.get(i, j)) - a.begin();
			dState.set(i, j, index);
		}
	}
}

int main() {
	freopen(fileinp, "r", stdin);
	//freopen(fileout, "w", stdout);//*/
	State::cnt = 0;
	State sState, dState;
	inputState(sState, dState);
	cout << "Start state: \n";
	sState.print();
	cout << "Desttnation state: \n";
	dState.print();
	preprocessing(sState, dState);
	
	State::heu = new Euclide();
	cout << "Euclide Heuristic\n";
	cout << "Solve step: " << processing(sState, dState) << "\n";
	cout << "Number of state: " << step << '\n';//*/
	
	State::heu = new Manhattan();
	cout << "Manhattan Heuristic\n";
	cout << "Solve step: " << processing(sState, dState) << "\n";
	cout << "Number of state: " << step << '\n';//*/
	
	State::heu = new LinearConflict();
	cout << "Linear Conflict + Manhattan Heuristic\n";
	cout << "Solve step: " << processing(sState, dState) << "\n";
	cout << "Number of state: " << step << '\n';//*/


	State::heu = new MisplacedTiles();
	cout << "Misplaced Tiles Heuristic\n";
	cout << "Solve step: " << processing(sState, dState) << "\n";
	cout << "Number of state: " << step << '\n';//*/

	State::heu = new Gaschnig();
	cout << "Gaschnig Heuristic\n";
	cout << "Solve step: " << processing(sState, dState) << "\n";
	cout << "Number of state: " << step << '\n';//*/
	
	State::heu = new Heuristic();
	cout << "No Heuristic\n";
	cout << "Solve step: " << processing(sState, dState) << "\n";
	cout << "Number of state: " << step << '\n';//*/

}

int processing(State sState, State dState) {
	map<State, int> g;
	priority_queue<pair<ii, State>> q;
	q.push(mkp(mkp(-1, -1), sState));
	//g[sState] = 1;
	step = 0;
	while (!q.empty()) {
		static pair<ii, State> top;
		static int gn;
		static int hn;
		static State curState;
		static map<State, int>::iterator it;
		top = q.top();
		q.pop();
		hn = -top.fi.fi;
		gn = -top.fi.se;
		step++;
		/*
		//bug-----------
		cout << "\n";
		//nxtState.print();
		cout << hn << " " << gn << " " << State::cnt << '\n';
		//bug-----------//*/
		curState = top.second;
		it = g.find(curState);
		if (it != g.end()) {
			static int gn_cur;
			gn_cur = it->se;
			if (gn_cur < gn) {
				continue;
			}
		}
		for (int k = 0; k < 4; ++k) {
			static int n = curState.getN();
			static int x;
			static int y;
			static State nxtState;
			static ii emptyPos;
			emptyPos = curState.getEmptyPos();
			x = orientX[k] + emptyPos.fi;
			y = orientY[k] + emptyPos.se;
			if (x >= n || y >= n || x < 0 || y < 0) {
				continue;
			}
			nxtState = curState.changeEmptyPos(x, y);
			it = g.find(nxtState);
			if (it != g.end()) {
				static int gn_nxt;
				gn_nxt = it->se;
				if (gn_nxt <= gn + 1) {
					continue;
				}
			}
			static int new_gn;
			static int new_hn;
			new_gn = gn + 1;
			new_hn = new_gn + nxtState.heuristic(dState);
			if (nxtState == dState) {
				return gn;
			}
			q.push(mkp(mkp(-new_hn, -new_gn), nxtState));
			g[nxtState] = new_gn;
		}
	}
	return 0;
}