#include "State.h"
using namespace std;
Heuristic* State::heu = new Heuristic();
void State::_deleteState() {
	if (state == NULL) {
		return;
	}
	for (int i = 0; i < n; ++i) {
		delete[] state[i];
	}
	delete[] state;
	n = 0;
	state = NULL;
}

State::State() {
	n = 0;
	_pos = ii(-1, -1);
	cnt++;
}

State::State(int n) {
	cnt++;
	set(n, "state n");
}

State::State(const State& A) {
	cnt++;
	int n = A.getN() * A.getN() - 1;
	set(n, "state a");
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			this->set(i, j, A.get(i, j), "state A");
		}
	}
}

State::~State() {
	cnt--;
	_deleteState();
}

void State::set(int n, string wh) {
	if (state != NULL) {
		_deleteState();
	}
	this->n = sqrt(n) + 1;
	state = new int* [this->n];
	for (int i = 0; i < this->n; ++i) {
		state[i] = new int[this->n];
	}
	_pos = mkp(-1, -1);
}

bool State::set(int i, int j, int val, string wh) {
	if (i >= n || j >= n || i < 0 || j < 0) {
		return false;
	}
	state[i][j] = val;
	if (val == 0) {
		_pos.fi = i;
		_pos.se = j;
	}
	return true;
}
/*
void setHeuristic(Heuristic _heu) {
	State::heu = _heu;
}//*/

int State::get(int i, int j) const {
	if (i >= n || j >= n || i < 0 || j < 0) {
		return -1;
	}
	return state[i][j];
}

int State::getN() const {
	return n;
}

State& State::operator=(const State& A) {
	if (state != NULL) {
		_deleteState();
	}
	set(A.n * A.n - 1);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			this->set(i, j, A.get(i, j), "=");
		}
	}
	return *this;
}//*/

bool State::operator<(const State& A) const {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (state[i][j] != A.get(i, j)) {
				return state[i][j] < A.get(i, j);
			}
		}
	}
	return false;
}

bool State::operator==(const State& A) const {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (state[i][j] != A.get(i, j)) {
				return false;
			}
		}
	}
	return true;
}

ii State::getEmptyPos() {
	return _pos;
}
State State::changeEmptyPos(int x, int y) {
	State res(*this);
	int val = res.get(x, y);
	res.set(_pos.fi, _pos.se, val, "empty pos");
	res.set(x, y, 0, "empty pos");
	return res;
}
int State::heuristic(State& s){
	//return heu->calc(n,state,s.state);
	return State::heu->calc(n,state,s.state);
}
//print
void State::print()const {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << state[i][j] << " ";
		}
		cout << "\n";
	}
}

