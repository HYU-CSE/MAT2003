#pragma once
#include "network.h"
#include <unordered_map>

#define NODE_ITER unordered_map<size_t, node*>::iterator
#define EDGE_ITER unordered_map<size_t, edge*>::iterator

/*---define---*/
#define FOR_EACH_NODE(TABLE, NODE_)	\
	node* NODE_ = (TABLE).begin()->second;\
	for(NODE_ITER iter = (TABLE).begin(); iter != (TABLE).end(); ++iter, (NODE_) = iter->second)

#define FOR_EACH_EDGE(TABLE, EDGE_)\
	edge* EDGE_ = (TABLE).begin()->second;\
	for(NODE_ITER iter = (TABLE).begin(); iter != (TABLE).end(); ++iter, (EDGE_) = iter->second)
/*---define---*/

class edgeTable {
private:
	unordered_map<size_t, edge*> list;
	nodeTable * nodes_ = new nodeTable();

	size_t insert(edge* node);
	void erase(size_t index);
public:
	edgeTable(nodeTable * nodes) : nodes_(nodes) { nodes->edges_ = this; }
	~edgeTable() {}

	EDGE_ITER begin();
	EDGE_ITER end();

	size_t add();
	size_t add(node * from, node * to);
	size_t add(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow);
	size_t add(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow, long color);

	void del(size_t index);
	void del(edge* edge);

	edge* find(size_t index);
	size_t find(edge* edge_);
};

class nodeTable {
private:
	unordered_map<size_t, node*> list;
	edgeTable * edges_ = new edgeTable(this);

	size_t insert(node* node);
	void erase(size_t index);
public:
	nodeTable() {}
	~nodeTable() {}

	edgeTable * edges();

	NODE_ITER begin();
	NODE_ITER end();

	size_t add();
	size_t add(int x, int y);
	size_t add(int x, int y, int r);
	size_t add(node* node);

	void del(size_t index);
	void del(node* node);

	node* find(size_t index);
	size_t find(node* node_);
	
	friend class edgeTable;
};

