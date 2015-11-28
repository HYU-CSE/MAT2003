#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
typedef struct edge_ {
	int from, to, cost, flow;
} edge;

class graph {
public:
	graph() {}
	~graph() {}
	size_t V;
	vector<edge*> edges;
	vector<vector<int>> cost;
	vector<vector<int>> flow;
private:
};

istream& operator>>(istream& is, graph& g)
{
	size_t e;
	is >> g.V >> e;
	while (e--)
	{
		edge * edge_ = new edge();
		is >> edge_->from >> edge_->to >> edge_->flow >> edge_->cost;
		g.edges.push_back(edge_);
	}
	g.cost.assign(g.V,vector<int>(g.V));
	g.flow.assign(g.V,vector<int>(g.V));
	for(edge * e : g.edges)
	{
		g.cost[e->from][e->to] = e->cost;
		g.flow[e->from][e->to] = e->flow;
	}
	return is;
}