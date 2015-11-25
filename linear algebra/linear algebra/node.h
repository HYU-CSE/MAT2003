#pragma once

#include <unordered_map>

#define NODE_ITER unordered_map<size_t, node*>::iterator

#define FOR_EACH_NODE(TABLE, ITER)	\
	for(NODE_ITER (ITER) = (TABLE).begin(); (ITER) != (TABLE).end(); (ITER)++)

using namespace std;

class node {
private:
public:
	int x, y, r = 30;

	node() {}
	node(int x, int y) : x(x), y(y) {}
	node(int x, int y, int r) : x(x), y(y), r(r) {}
	~node() {}
};

class nodeTable {
private:
	unordered_map<size_t, node*> list;

	size_t insert(node* node);
	void erase(size_t index);
public:
	nodeTable() {}
	~nodeTable() {}

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
};