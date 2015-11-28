#pragma once

#include <vector>

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

#define NODE_ITER vector<node*>::iterator
#define FOR_EACH_NODE(TABLE, IDX)	\
	for(size_t (IDX) = 0; (IDX) < (TABLE).size(); (IDX)++)

class nodeTable {
private:
	vector<node*> nodes;

	size_t max_dx = 0;
	size_t insert(node* node);
	void erase(node* index);
	void erase(size_t index);
public:
	nodeTable() {}
	~nodeTable() {}

	NODE_ITER begin();
	NODE_ITER end();

	size_t size();
	node * at(size_t index);

	size_t add();
	size_t add(int x, int y);
	size_t add(int x, int y, int r);
	size_t add(node* node);
	
	void del(size_t index);
	void del(node* node);

	node* find(size_t index);
	size_t find(node* node_);
};