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

	std::vector<edge> adj[10010]; // 첫번째 to, 두번째 capacity
	int level[10010];
	int iter[10010];

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

int input[101][101], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		dinic flow;
		int n;
		scanf("%d", &n);

		auto node = [&](int a, int b) {return (a - 1) * 51 + b - 1; };

		int source = node(51, 51) + 1, sink = node(51, 51) + 2;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int a, b;
				scanf("%d.%d", &a, &b);

				input[i][j] = a * 100 + b;
				flow.add_edge(source, node(i, j), input[i][j]);
				flow.add_edge(node(i, j), sink, 100 - input[i][j]);
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 0; k < 4; k++) {
					int nx = i + mov[k][0], ny = j + mov[k][1];
					if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
						continue;

					flow.add_edge(node(i, j), node(nx, ny), 100 - aabs(input[i][j] - input[nx][ny]));
				}
			}
		}

		int result = 100 * n * n - flow.max_flow(source, sink);
		printf("%d.%02d\n", result / 100, result % 100);
	}
}