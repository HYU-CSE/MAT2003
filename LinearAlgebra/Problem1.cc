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

int MaximumFlow(const graph& g, int s, int t)
{
	//maximum flow == return value
	int maxflow = 0;

	//res is Residual graph
	vector<vector<int>> res(g.flow.begin(), g.flow.end());
	
	//parent mean where vertex from
	vector<int> parent(g.V);

	//bfs function for search route
	function<bool(int, int)> bfs = [&](int s, int t)->bool {

		//queue for bfs
		queue<int> qu;

		//visited check
		vector<bool> visited(g.V, false);

		//visit function for visit [add queue, visit check, parent check]
		function<void(int, int)> visit = [&](int v, int u)->void {
			qu.push(v);
			visited[v] = true;
			parent[v] = u;
		};

		visit(s, -1);
		while (qu.size())
		{
			int n = qu.front(); qu.pop();

			//for loop n to v
			for (size_t v = 0; v < g.V; v++)
				if (!visited[v] && res[n][v] > 0)
					visit(v, n);
		}

		return visited[t] == true;
	};

	//bfs loop, if (s to t) is true
	while (bfs(s, t))
	{
		//init pathflow INF, for renewal
		int pathflow = INF;
		//renewal pathflow
		for (size_t v = t; v != s; v = parent[v])
			pathflow = min(pathflow, res[parent[v]][v]);

		for (size_t v = t; v != s; v = parent[v])
		{
			res[parent[v]][v] -= pathflow;
			res[v][parent[v]] += pathflow;
		}

		//add pathflow to maxflow
		maxflow += pathflow;
	}

	//return maxflow
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