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

std::pair<int, int> IC[110], PC[110];

int main(void) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	dinic flow;
	int source = 2000, sink = 2001, new_source = 2002, new_sink = 2003, sum = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d", &IC[i].first);
		flow.add_edge(source, new_sink, IC[i].first);
		flow.add_edge(new_source, i, IC[i].first);
		sum += IC[i].first;
	}

	for (int i = 0; i < n; i++) {
		scanf("%d", &IC[i].second);
		flow.add_edge(source, i, IC[i].second - IC[i].first);
	}

	for (int i = 0; i < m; i++) {
		scanf("%d", &PC[i].first);
		flow.add_edge(i + n, new_sink, PC[i].first);
		flow.add_edge(new_source, sink, PC[i].first);
		sum += PC[i].first;
	}

	for (int i = 0; i < m; i++) {
		scanf("%d", &PC[i].second);
		flow.add_edge(i + n, sink, PC[i].second - PC[i].first);
	}

	for (int i = 0; i < k; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		flow.add_edge(a - 1, b + n - 1, 1);
	}

	flow.add_edge(sink, source, INT_MAX / 2);

	int result1 = flow.max_flow(new_source, new_sink), result2 = flow.max_flow(source, sink);
	if (result1 == sum) {
		printf("%d\n", result2);
	}
	else {
		printf("-1\n");
	}
}