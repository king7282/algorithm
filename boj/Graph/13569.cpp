#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <limits.h>
#include <algorithm>

struct dinic {
	struct edge {
		int to, cap, rev;
		edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
	};

	std::vector<edge> adj[4110]; // 첫번째 to, 두번째 capacity
	int level[4110];
	int iter[4110];

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

std::pair<int, int> table[210][210], rows[210], colunms[210];
int rows_node[210], column_node[210];
int result[210][210];

int main(void) {
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	int cnt = 4, limits;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d.%d", &a, &b);
			if (b == 0)
				table[i][j].first = table[i][j].second = a;
			else {
				table[i][j].first = a;
				table[i][j].second = a + 1;
			}
		}

		scanf("%d.%d", &a, &b);
		if (b == 0)
			rows[i].first = rows[i].second = a;
		else {
			rows[i].first = a;
			rows[i].second = a + 1;
		}
		rows_node[i] = cnt++;
	}

	limits = cnt;

	for (int i = 0; i < m; i++) {
		scanf("%d.%d", &a, &b);
		if (b == 0)
			colunms[i].first = colunms[i].second = a;
		else {
			colunms[i].first = a;
			colunms[i].second = a + 1;
		}
		column_node[i] = cnt++;
	}

	int source = 0, sink = 1, new_source = 2, new_sink = 3;
	dinic flow;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int start = rows_node[i], finish = column_node[j];
			flow.add_edge(start, finish, table[i][j].second - table[i][j].first);
			flow.add_edge(start, new_sink, table[i][j].first);
			flow.add_edge(new_source, finish, table[i][j].first);
		}
	}

	for (int i = 0; i < n; i++) {
		int node = rows_node[i];
		flow.add_edge(source, node, rows[i].second - rows[i].first);
		flow.add_edge(source, new_sink, rows[i].first);
		flow.add_edge(new_source, node, rows[i].first);
	}

	for (int i = 0; i < m; i++) {
		int node = column_node[i];
		flow.add_edge(node, sink, colunms[i].second - colunms[i].first);
		flow.add_edge(node, new_sink, colunms[i].first);
		flow.add_edge(new_source, sink, colunms[i].first);
	}

	flow.add_edge(sink, source, INT_MAX / 2);

	flow.max_flow(new_source, new_sink);
	flow.max_flow(source, sink);

	for (int i = 0; i < flow.adj[source].size(); i++) {
		int node = flow.adj[source][i].to;
		if (new_sink < node && node < limits) {
			if (flow.adj[source][i].cap == 0) {
				result[node - new_sink - 1][m] = rows[node - new_sink - 1].second;
			}
			else {
				result[node - new_sink - 1][m] = rows[node - new_sink - 1].first;
			}
		}
	}

	for (int i = 0; i < flow.adj[sink].size(); i++) {
		int node = flow.adj[sink][i].to;
		if (limits <= node && node < cnt) {
			if (flow.adj[sink][i].cap == 0) {
				result[n][node - limits] = colunms[node - limits].first;
			}
			else
				result[n][node - limits] = colunms[node - limits].second;
		}
	}

	for (int i = new_sink + 1; i < limits; i++) {
		for (int j = 0; j < flow.adj[i].size(); j++) {
			int node = flow.adj[i][j].to;

			if (limits <= node && node < cnt) {
				int x = i - new_sink - 1, y = node - limits;
				if (flow.adj[i][j].cap == 0) {
					result[x][y] = table[x][y].second;
				}
				else
					result[x][y] = table[x][y].first;
			}
		}
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (!(i == n && j == m)) {
				printf("%d ", result[i][j]);
			}
		}
		printf("\n");
	}
}