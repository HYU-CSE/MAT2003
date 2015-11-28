#pragma once

#include <vector>

#include "node.h"

#define COST_TYPE int
#define FLOW_TYPE int

using namespace std;

class edge {
private:
public:
	node *from, *to;
	long color;
	COST_TYPE cost;
	FLOW_TYPE flow;

	edge() {}
	edge(node * from, node * to) :
		from(from), to(to) {}
	edge(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow) :
		from(from), to(to), cost(cost), flow(flow) {}
	edge(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow, long color) :
		from(from), to(to), cost(cost), flow(flow), color(color) {}
	~edge() {}
	
	bool operator==(const edge& e) { return e.to == this->to && e.from == this->from && e.cost == this->cost && e.flow == this->flow; }
};

#define EDGE_ITER vector<edge*>::iterator

#define FOR_EACH_EDGE(TABLE, IDX)	\
	for(size_t (IDX) = 0; IDX < (TABLE).size(); (IDX)++)

class edgeTable {
private:
	vector<edge*> edges;
	nodeTable * nodes;

	size_t insert(edge* edge);
	void erase(edge* edge);
	void erase(size_t index);
public:
	edgeTable(nodeTable* nodes) : nodes(nodes) {}
	~edgeTable() {}

	EDGE_ITER begin();
	EDGE_ITER end();

	size_t size();
	edge* at(size_t index);

	size_t add();
	size_t add(size_t from, size_t to);
	size_t add(size_t from, size_t to, COST_TYPE cost, FLOW_TYPE flow);
	size_t add(size_t from, size_t to, COST_TYPE cost, FLOW_TYPE flow, long color);
	size_t add(node * from, node * to);
	size_t add(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow);
	size_t add(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow, long color);

	void del(size_t index);
	void del(edge* edge);
	void del(node* node);

	friend class node;
};