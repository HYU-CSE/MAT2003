#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

#include "graph.h"
#include "measure.h"

#define INF 123456789

using namespace std;
int MaximumFlow(const graph& g, int s, int t)
{
	//maximum flow == return value
	int maxflow = 0;

	//res is Residual graph
	vector<vector<int>> res(g.flow.begin(), g.flow.end());
	//parent present where from
	vector<int> parent(g.V, -1);

	//bfs function for search route
	function<bool(int, int)> bfs = [&](int s, int t)->bool{
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
			for (int v = 0; v < g.V; v++)
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
		for (int v = t; v != s; v = parent[v])
			pathflow = min(pathflow, res[parent[v]][v]);

		for (int v = t; v != s; v = parent[v])
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
	//get information of graph
	fstream fs("graph", std::ios::in);
	istream * is = &fs;
	graph g;
	*is >> g;

	//test 10 times
	TIME_TEST(test, 1000)
	{
		MaximumFlow(g, 0, 13);
	}
	
	//result 
	cout << "result: " << MaximumFlow(g, 0, 13) << endl;

	//execution time
	cout << "execution time(" << test.repeat << ") total: " << test.total << ", average: " << test.average<< endl;
	return 0;
}