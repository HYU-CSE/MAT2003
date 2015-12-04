#include <vector>
#include <iostream>

using namespace std;

typedef struct edge_ {
	int from, to, cost, flow;
} edge;

class graph {
public:
	graph() {}
	~graph() {}
	size_t V, E;
	vector<edge*> edges;
	vector<vector<int>> cost;
	vector<vector<int>> flow;
	vector<vector<pair<size_t, int>>> to_cost;
	vector<vector<pair<size_t, int>>> to_flow;
private:
};

istream& operator>>(istream& is, graph& g)
{
	is >> g.V >> g.E;
	g.to_cost.assign(g.V,vector<pair<size_t,int>>());
	g.to_flow.assign(g.V,vector<pair<size_t,int>>());
	g.cost.assign(g.V,vector<int>(g.V));
	g.flow.assign(g.V,vector<int>(g.V));
	while (g.E--)
	{
		edge * edge_ = new edge();
		is >> edge_->from >> edge_->to >> edge_->flow >> edge_->cost;
		g.to_cost[edge_->from].push_back({ edge_->to,edge_->cost });
		g.to_flow[edge_->from].push_back({ edge_->to,edge_->flow });
		g.cost[edge_->from][edge_->to] = edge_->cost;
		g.flow[edge_->from][edge_->to] = edge_->flow;
		g.edges.push_back(edge_);
	}
	g.E = g.edges.size();
	return is;
}