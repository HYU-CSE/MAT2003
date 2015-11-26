#include "edge.h"

size_t edgeTable::insert(edge* edge)
{
	size_t ret = this->list.size();
	this->list.insert(edge);
	return ret;
}
void edgeTable::erase(edge* edge)
{
	this->list.erase(edge);
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
size_t edgeTable::add(size_t from, size_t to)
{
	return this->add(this->nodes->find(from), this->nodes->find(to));
}
size_t edgeTable::add(size_t from, size_t to, COST_TYPE cost, FLOW_TYPE flow)
{
	return this->add(this->nodes->find(from), this->nodes->find(to), cost, flow);
}
size_t edgeTable::add(size_t from, size_t to, COST_TYPE cost, FLOW_TYPE flow, long color)
{
	return this->add(this->nodes->find(from), this->nodes->find(to), cost, flow, color);
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

void edgeTable::del(node* node)
{
	for (EDGE_ITER iter = this->list.begin(); iter != this->list.end();)
	{
		if ((*iter)->from == node || (*iter)->to == node)
			iter = this->list.erase(iter);
		else
			iter++;
	}
}