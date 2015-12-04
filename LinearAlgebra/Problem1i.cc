#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>

//header include
#include "headers\graph.h"
#include "headers\measure.h"
#include "headers\fileIO.h"

#define INF 123456789

bool print = false;
using namespace std;

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};

int MaximumFlow(const graph& g, int s, int t)
{
	vector<vector<Edge>> G(g.V);

	int maxflow = 0;

	function<void(int, int, int)> addEdge = [&](int from, int to, int cap)->void {
		G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
		if (from == to)
			G[from].back().index++;
		G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
	};

	for (int i = 0; i < g.V; i++)
		for (pair<size_t, int> p : g.to_flow[i])
			addEdge(i, p.first, p.second);

	function<int(int, int)> search = [&](int s, int t)->int {
		vector<Edge *> parent(g.V, (Edge*)NULL);

		vector<int> qu(g.V);
		parent[s] = &G[0][0] - 1;
		int start = 0, end = 0;

		qu[end++] = s;

		while (start < end)
		{
			int u = qu[start++];
			for (int v = 0; v < G[u].size(); v++)
			{
				Edge &e = G[u][v];
				if (!parent[e.to] && e.cap - e.flow > 0)
				{
					parent[e.to] = &G[u][v];
					qu[end++] = e.to;
				}
			}
		}

		if (!parent[t])
			return 0;

		int tflow = 0;
		for (int i = 0; i < G[t].size(); i++)
		{
			Edge * edge = &G[G[t][i].to][G[t][i].index];
			int bot = INF;
			for (Edge *e = edge; bot && e != parent[s]; e = parent[e->from])
			{
				if (!e)
				{
					bot = 0;
					break;
				}
				bot = min(bot, e->cap - e->flow);
			}
			if (!bot)
				continue;

			for (Edge *e = edge; bot && e != parent[s]; e = parent[e->from])
			{
				e->flow += bot;
				G[e->to][e->index].flow -= bot;
			}
			tflow += bot;
		}
		return tflow;
	};


	while (int flow = search(s, t))
		maxflow += flow;

	return maxflow;
}
int main(int argc, char * argv[])
{
	//when custom file inputed
	if (argc > 1)
	{
		fstream ffs(argv[1], std::ios::in);
		graph g;
		ffs >> g;

		//test 1000 times
		int rresult = 0;
		TIME_TEST(test, 10000)
		{
			rresult = MaximumFlow(g, 0, g.V - 1);
		}

		string res("result: maxflow: " + to_string(rresult));
		TEST_END(test, argv[0], res);
		return 0;
	}

	//default setting
	string file = "data\\graph";
	//each graph0~10
	FILE_TEST(file, 10)
	{
		fstream fs(file, std::ios::in);
		graph g;
		fs >> g;

		//test 1000 times
		int result = 0;
		TIME_TEST(test, 10000)
		{
			result = MaximumFlow(g, 0, g.V - 1);
		}

		string res("result: maxflow: " + to_string(result));
		TEST_END(test, file, res);
	}

	return 0;
}