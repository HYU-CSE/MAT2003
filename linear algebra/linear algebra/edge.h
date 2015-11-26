#pragma once

#include <unordered_set>

#include "node.h"

#define COST_TYPE int
#define FLOW_TYPE int

#define EDGE_ITER unordered_set<edge*>::iterator

#define FOR_EACH_EDGE(TABLE, ITER)	\
	for(EDGE_ITER (ITER) = (TABLE).begin(); (ITER) != (TABLE).end(); (ITER)++)

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
};

class edgeTable {
private:
	unordered_set<edge*> list;
	nodeTable * nodes;

	size_t insert(edge* edge);
	void erase(edge* edge);
public:
	edgeTable(nodeTable* nodes) : nodes(nodes) {}
	~edgeTable() {}

	EDGE_ITER begin();
	EDGE_ITER end();

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