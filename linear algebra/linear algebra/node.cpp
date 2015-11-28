#include "node.h"

size_t nodeTable::insert(node* node_)
{
	for (NODE_ITER iter = this->nodes.begin(); iter != this->nodes.end(); iter++)
		if ((*iter) == node_)
			return -1;
	this->nodes.push_back(node_);
	return this->nodes.size() - 1;
}
void nodeTable::erase(node* node_)
{
	for (NODE_ITER iter = this->nodes.begin(); iter != this->nodes.end(); iter++)
		if ((*iter) == node_)
		{
			this->nodes.erase(iter);
			break;
		}
}
void nodeTable::erase(size_t value)
{
	this->nodes.erase(this->nodes.begin() + value);
}
size_t nodeTable::find(node* node_)
{
	size_t idx = 0;
	for (NODE_ITER iter = this->nodes.begin(); iter != this->nodes.end(); iter++, idx++)
		if ((*iter) == node_)
			return idx;
	return 0;
}
node* nodeTable::find(size_t value)
{
	if (value < this->nodes.size())
		return this->nodes[value];
	return nullptr;
}

NODE_ITER nodeTable::begin()
{
	return this->nodes.begin();
}
NODE_ITER nodeTable::end()
{
	return this->nodes.end();
}

size_t nodeTable::size()
{
	return this->nodes.size();
}
node * nodeTable::at(size_t index)
{
	return this->nodes[index];
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
	return this->erase(this->find(index));
}
void nodeTable::del(node* node)
{
	return this->erase(node);
}