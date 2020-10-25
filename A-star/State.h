#pragma once
#include <string>
#include<iostream>
#include<stdio.h>
#include <functional>
#include"Heuristic.h"
using namespace std;

struct State {
private:
	int n;
	ii _pos;
	void _deleteState();
protected:
	int** state = NULL;
public:
	static Heuristic* heu;
	static int cnt;
	//constructor-destructor
	State();
	State(int n);
	State(const State& A);
	~State();
	//geter-seter
	void set(int n, string wh = "no");
	bool set(int i, int j, int val, string wh = "no"); 
	int get(int i, int j) const;
	int getN() const;
	//operator
	State& operator=(const State& A);
	bool operator<(const State& A) const;
	bool operator==(const State& A) const;
	//processing
	ii getEmptyPos();
	State changeEmptyPos(int x, int y);
	int heuristic(State& s);
	//print
	void print()const;
};
//void setHeuristic(Heuristic _heu);
