#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <climits>
#include <queue>

struct dinic {
	struct edge {
		int to, cap, rev;
		edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
	};

	std::vector<edge> adj[2010]; // 첫번째 to, 두번째 capacity
	int level[2010];
	int iter[2010];

	void add_edge(int from, int to, int capacity) {
		adj[from].push_back(edge(to, capacity, adj[to].size()));
		adj[to].push_back(edge(from, 0, adj[from].size() - 1));
	}

	void bfs(int start) {
		memset(level, -1, sizeof(level));

		level[start] = 0;
		std::queue<int> qu;
		qu.push(start);
		while (!qu.empty()) {
			int f = qu.front();
			qu.pop();

			for (int i = 0; i < adj[f].size(); i++) {
				if (adj[f][i].cap > 0 && level[adj[f][i].to] < 0) {
					level[adj[f][i].to] = level[f] + 1;
					qu.push(adj[f][i].to);
				}
			}
		}
	}

	int dfs(int num, int finish, int cap) {
		if (num == finish) return cap;
		for (int &i = iter[num]; i < adj[num].size(); i++) {
			if (adj[num][i].cap > 0 && level[num] < level[adj[num][i].to]) {
				int d = dfs(adj[num][i].to, finish, std::min(cap, adj[num][i].cap));
				if (d > 0) {
					adj[num][i].cap -= d;
					adj[adj[num][i].to][adj[num][i].rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	int max_flow(int start, int finish) {
		int result = 0;
		while (1) {
			bfs(start);
			if (level[finish] == -1)
				return result;
			memset(iter, 0, sizeof(iter));
			int tmp;
			while ((tmp = dfs(start, finish, INT_MAX / 2)) > 0)
				result += tmp;
		}
	}
};

struct edge {
	int x, y, weights;
	edge(int x, int y, int weights) : x(x), y(y), weights(weights) {}
};

std::vector<edge> graph;

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		graph.push_back(edge(a, b, c));
	}

	std::sort(graph.begin(), graph.end(), [](edge a, edge b) {
		return a.weights < b.weights;
		});

	int result = 0;
	for (int i = 0; i < graph.size(); i++) {
		dinic flow;
		for (int j = i - 1; j >= 0; j--) {
			if (graph[i].weights == graph[j].weights)
				continue;

			flow.add_edge(graph[j].x, graph[j].y, 1);
			flow.add_edge(graph[j].y, graph[j].x, 1);
		}

		flow.add_edge(0, graph[i].x, INT_MAX / 2);
		flow.add_edge(graph[i].y, n + 1, INT_MAX / 2);
		result += flow.max_flow(0, n + 1);
	}

	printf("%d\n", result);
}