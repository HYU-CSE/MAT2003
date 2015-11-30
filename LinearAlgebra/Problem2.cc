#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>

#include "headers\graph.h"
#include "headers\measure.h"
#include "headers\fileio.h"

#define INF 123456789

bool print = false;
using namespace std;

int mincostflow(const graph& g, const int& s, const int& t, const int& f)
{
	vector<vector<int>> cost(g.cost.begin(), g.cost.end());
	vector<vector<int>> cap(g.flow.begin(), g.flow.end()), flow(g.V, vector<int>(g.V));
	vector<int> label(g.V, 0);
	vector<pair<int, bool>> parent(g.V, { -1,-1 });

	function <bool(void)> bellmanford = [&cost, &flow, &cap, &label, &parent, &s, &t](void)->bool {
		int V = cost.size();
		int u = s;
		vector<bool> found(V, false);
		vector<int> dist(V, INF), width(V, 0);

		function<void(int s, int t, int cap, int cost, bool dir)> relax = [&](int s, int t, int cap, int cost, bool dir)->void {
			int value = dist[s] + label[s] - label[t] + cost;
			if (cap && value < dist[t])
			{
				dist[t] = value;
				parent[t] = { s, dir };
				width[t] = min(cap, width[s]);
			}
		};

		dist[u] = 0;
		width[u] = INF;

		while (u != -1)
		{
			int best = -1;
			found[u] = true;
			for (int v = 0; v < V; v++)
			{
				if (found[v])
					continue;
				relax(u, v, cap[u][v] - flow[u][v], cost[u][v], true);
				relax(u, v, flow[v][u], -cost[v][u], false);

				if (best == -1 || dist[v] < dist[best])
					best = v;
			}
			u = best;
		}

		for (int k = 0; k < V; k++)
			label[k] = min(label[k] + dist[k], INF);

		return width[t];
	};

	int tflow = 0, tcost = 0;

	while (int bot = bellmanford())
	{
		if (bot > f - tflow)
			bot = f - tflow;
		tflow += bot;
		for (int k = t; k != s; k = parent[k].first)
		{
			if (parent[k].second)
			{
				flow[parent[k].first][k] += bot;
				tcost += bot * cost[parent[k].first][k];
			}
			else
			{
				flow[k][parent[k].first] -= bot;
				tcost -= bot * cost[k][parent[k].first];
			}
		}
		if (tflow == f)
			break;
	}
	if (tflow < f)
		return 0;
	return tcost;
}

int main(int argc, char * argv[])
{
	if (argc > 1)
	{
		fstream ffs(argv[1], std::ios::in);
		graph g;
		ffs >> g;

		int fflow = 3;
		if (argc>2)
			fflow = atoi(argv[2]);

		//test 10 times
		int rresult = 0;
		TIME_TEST(test, 100)
		{
			rresult = mincostflow(g, 0, g.V - 1, fflow);
		}

		string res("result: given flow: " + to_string(fflow) + ", cost: " + to_string(rresult));
		TEST_END(test, argv[0], res);
		return 0;
	}

	int flow = 9;

	string file = "data\\graph";
	FILE_TEST(file, 10)
	{
		fstream fs(file, std::ios::in);
		graph g;
		fs >> g;

		//test 10 times
		int result = 0;
		TIME_TEST(test, 1000)
		{
			result = mincostflow(g, 0, g.V - 1, flow);
		}

		string res("result: given flow: " + to_string(flow) + ", cost: " + to_string(result));
		TEST_END(test, file, res);
	}

	return 0;
}