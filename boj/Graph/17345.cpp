#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <limits.h>

struct dinic {
	struct edge {
		int to, cap, rev;
		edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
	};

	std::vector<edge> adj[55020]; // 첫번째 to, 두번째 capacity
	int level[55020];
	int iter[55020];

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

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	int source = n + m + 1, sink = n + m + 2;
	dinic flow;

	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);

		flow.add_edge(source, i, a);
	}

	int result = 0;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		flow.add_edge(i + n, sink, c);
		flow.add_edge(a - 1, i + n, INT_MAX / 2);
		flow.add_edge(b - 1, i + n, INT_MAX / 2);
		result += c;
	}

	printf("%d\n", result - flow.max_flow(source, sink));
}
