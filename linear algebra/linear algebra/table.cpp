#include "table.h"

size_t nodeTable::insert(node* node)
{
	size_t ret = this->list.size();
	this->list.insert({ this->list.size(), node });
	return ret;
}
void nodeTable::erase(size_t index)
{
	this->list.erase(this->find(index));
}
size_t nodeTable::find(node* node_)
{
	for (NODE_ITER iter = this->list.begin(); iter != this->list.end(); iter++)
		if (iter->second == node_)
			return iter->first;
	return 0;
}
node* nodeTable::find(size_t value)
{
	for (NODE_ITER iter = this->list.begin(); iter != this->list.end(); iter++)
		if (iter->first == value)
			return iter->second;
	return nullptr;
}

edgeTable* nodeTable::edges() 
{
	return this->edges_;
}

NODE_ITER nodeTable::begin()
{
	return this->list.begin();
}
NODE_ITER nodeTable::end()
{
	return this->list.end();
}


size_t nodeTable::add()
{
	node * node_ = new node();
	return this->insert(node_);
}
size_t nodeTable::add(int x, int y)
{
	node * node_ = new node(x, y);
	return this->insert(node_);
}
size_t nodeTable::add(int x, int y, int r)
{
	node * node_ = new node(x, y, r);
	return this->insert(node_);
}
size_t nodeTable::add(node* node)
{
	return this->insert(node);
}

void nodeTable::del(size_t index)
{
	return this->erase(index);
}
void nodeTable::del(node* node)
{
	return this->erase(this->find(node));
}



size_t edgeTable::insert(edge* edge)
{
	size_t ret = this->list.size();
	this->list.insert({ this->list.size(), edge });
	return ret;
}
void edgeTable::erase(size_t index)
{
	this->list.erase(index);
}

size_t edgeTable::find(edge* edge_)
{
	for (EDGE_ITER iter = this->list.begin(); iter != this->list.end(); iter++)
		if (iter->second == edge_)
			return iter->first;
	return 0;
		
}
edge* edgeTable::find(size_t value)
{
	for (EDGE_ITER iter = this->list.begin(); iter != this->list.end(); iter++)
		if (iter->first == value)
			return iter->second;
	return nullptr;
}

EDGE_ITER edgeTable::begin()
{
	return this->list.begin();
}
EDGE_ITER edgeTable::end()
{
	return this->list.end();
}


size_t edgeTable::add()
{
	edge * edge_ = new edge();
	return this->insert(edge_);
}
size_t edgeTable::add(node * from, node * to)
{
	edge * edge_ = new edge(from, to);
	return this->insert(edge_);
}
size_t edgeTable::add(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow)
{
	edge * edge_ = new edge(from, to, cost, flow);
	return this->insert(edge_);
}
size_t edgeTable::add(node * from, node * to, COST_TYPE cost, FLOW_TYPE flow, long color)
{
	edge * edge_ = new edge(from, to, cost, flow, color);
	return this->insert(edge_);
}

void edgeTable::del(size_t index)
{
	return this->erase(index);
}
void edgeTable::del(edge* edge)
{
	return this->erase(this->find(edge));
}
