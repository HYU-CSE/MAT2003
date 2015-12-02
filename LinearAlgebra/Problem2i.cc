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

int mincostflow(const graph& g, const int& s, const int& t, const int& f)
{
	//cost, cap=capacity, flow
	vector<vector<int>> cost(g.cost.begin(), g.cost.end());
	vector<vector<int>> cap(g.flow.begin(), g.flow.end()), flow(g.V, vector<int>(g.V));

	//label for check
	vector<int> label(g.V, 0);

	//parent mean where vertex from
	vector<pair<int, bool>> parent(g.V, { -1,-1 });

	//find path by dijkstra
	function <int(void)> findpath = [&cost, &flow, &cap, &label, &parent, &s, &t](void)->int {
		//V mean N(number of vertex)
		int V = cost.size();
		pair<int, int> u = {s, 0};

		//dist[n] mean distance s to n
		//width for return bottleneck of path
		vector<int> dist(V, INF), width(V, 0);

		priority_queue<pair<int,int>> qu;

		//relax for renew
		function<void(int s, int t, int cap, int cost, bool dir)> relax = [&](int s, int t, int cap, int cost, bool dir)->void {
			int value = dist[s] + label[s] - label[t] + cost;
			if (cap && value < dist[t])
			{
				dist[t] = value;
				parent[t] = { s, dir };
				width[t] = min(cap, width[s]);
				qu.push({t, dist[t]});
			}
		};

		qu.push(u);
		dist[u.first] = 0;
		width[u.first] = INF;

		while (qu.size())
		{
			u = qu.top(); qu.pop();
			if(u.first == V)
				break;

			for(int v = 0; v < V; v++)
			{
				relax(u.first, v, cap[u.first][v] - flow[u.first][v], cost[u.first][v], true);
				relax(u.first, v, flow[v][u.first], -cost[v][u.first], false);
			}
		}

		//check label for minimum value
		for (int k = 0; k < V; k++)
			label[k] = min(label[k] + dist[k], INF);

		return width[t];
	};

	//tflow = total flow,
	//tcost = total cost;
	int tflow = 0, tcost = 0;

	while (int bot = findpath())
	{
		//if bottleneck (bot){min of flow in path} + tflow > f(given flow) set bot to f - tflow; (interupt exceed)
		if (bot > f - tflow)
			bot = f - tflow;
		tflow += bot;

		//when path finded. renew flow and cost
		//cost *= -1
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

		//when tflow == f(given flow) finish loop
		if (tflow == f)
			break;
	}
	if (tflow < f)
		return 0;
	return tcost;
}

int main(int argc, char * argv[])
{
	//when custom file inputed
	if (argc > 1)
	{
		fstream ffs(argv[1], std::ios::in);
		graph g;
		ffs >> g;

		int fflow = 9;
		if (argc>2)
			fflow = atoi(argv[2]);

		//test 1000 times
		int rresult = 0;
		TIME_TEST(test, 1000)
		{
			rresult = mincostflow(g, 0, g.V - 1, fflow);
		}

		string res("result: given flow: " + to_string(fflow) + ", cost: " + to_string(rresult));
		TEST_END(test, argv[0], res);
		return 0;
	}

	//default setting
	int flow = 9;

	string file = "data\\graph";
	//each graph0~10
	FILE_TEST(file, 10)
	{
		fstream fs(file, std::ios::in);
		graph g;
		fs >> g;

		//test 1000 times
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