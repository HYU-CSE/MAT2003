#pragma once

#define COST_TYPE int
#define FLOW_TYPE int

using namespace std;

class node {
private:
public:
	int x_, y_, r_ = 30;

	node() {}
	node(int x, int y) : x_(x), y_(y) {}
	node(int x, int y, int r) : x_(x), y_(y), r_(r) {}
	~node() {}
};

class edge {
private:
public:
	node *from_, *to_;
	long color_;
	COST_TYPE cost_;
	FLOW_TYPE flow_;

	edge() {}
	edge( node * from, node * to) :
		from_(from), to_(to) {}
	edge(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow) :
		from_(from), to_(to), cost_(cost), flow_(flow) {}
	edge(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow, long color) :
		from_(from), to_(to), cost_(cost), flow_(flow), color_(color) {}
	~edge() {}
};