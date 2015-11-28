#include "edge.h"

size_t edgeTable::insert(edge* edge_)
{
	for (EDGE_ITER iter = this->edges.begin(); iter != this->edges.end(); iter++)
		if ((*iter) == edge_)
			return -1;
	this->edges.push_back(edge_);
	return this->edges.size() - 1;
}
void edgeTable::erase(size_t index)
{
	this->edges.erase(this->edges.begin() + index);
}
void edgeTable::erase(edge* edge_)
{
	for (EDGE_ITER iter = this->edges.begin(); iter != this->edges.end(); iter++)
		if ((*iter) == edge_)
		{
			this->edges.erase(iter);
			return;
		}
}

EDGE_ITER edgeTable::begin()
{
	return this->edges.begin();
}
EDGE_ITER edgeTable::end()
{
	return this->edges.end();
}

size_t edgeTable::size()
{
	return this->edges.size();
}
edge* edgeTable::at(size_t index)
{
	return this->edges[index];
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
	for (EDGE_ITER iter = this->edges.begin(); iter != this->edges.end();)
	{
		if ((*iter)->from == node || (*iter)->to == node)
			iter = this->edges.erase(iter);
		else
			iter++;
	}
}