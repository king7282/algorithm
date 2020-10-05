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

	std::vector<edge> adj[3010]; // 첫번째 to, 두번째 capacity
	int level[3010];
	int iter[3010];

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

int trans[3010];
bool check[110];
std::vector<int> result1[110];

int main(void) {
	int n, m, s, e;
	scanf("%d %d %d %d", &n, &m, &s, &e);

	int source = 3000, sink = 3001, new_source = 3002, new_sink = 3003;
	dinic flow;
	int sum = 0;

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		flow.add_edge(i, sink, b - a);
		flow.add_edge(i, new_sink, a);
		flow.add_edge(new_source, sink, a);
		sum += a;
	}

	int cnt = n + m;
	for (int i = 0; i < n; i++) {
		flow.add_edge(source, m + i, e - s);
		flow.add_edge(source, new_sink, s);
		flow.add_edge(new_source, m + i, s);
		sum += s;

		int k;
		scanf("%d", &k);
		memset(check, false, sizeof(check));

		for (int j = 0; j < k; j++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);

			flow.add_edge(m + i, cnt, (c - b + 1) - a);
			trans[cnt] = i;
			for (int z = b - 1; z < c; z++) {
				flow.add_edge(cnt, z, 1);
				check[z] = true;
			}
			cnt++;
		}

		for (int j = 0; j < m; j++) {
			if (check[j] == false) {
				flow.add_edge(m + i, new_sink, 1);
				flow.add_edge(new_source, j, 1);
				sum++;
			}
		}
	}

	flow.add_edge(sink, source, INT_MAX / 2);
	int tmp = flow.max_flow(new_source, new_sink);
	int result = flow.max_flow(source, sink);
	if (tmp == sum) {
		printf("1\n");

		for (int i = 0; i < m; i++) {
			memset(check, false, sizeof(check));
			
			for (int j = 0; j < flow.adj[i].size(); j++) {
				int next = flow.adj[i][j].to;
				if (next >= n + m && next < cnt) {
					if (flow.adj[i][j].cap == 0) {
						check[trans[next]] = true;
					}
				}
				else if (m <= next && next < m + n) {
					if (flow.adj[i][j].cap == 0) {
						check[next - m] = true;
					}
				}
			}

			for (int j = 0; j < n; j++) {
				if (check[j] == true)
					result1[j].push_back(i + 1);
			}
		}

		for (int i = 0; i < n; i++) {
			if (result1[i].size() == 0) {
				if (i == n - 1)
					printf("0");
				else
					printf("0\n");
			}
			else
				printf("%d ", result1[i].size());

			std::sort(result1[i].begin(), result1[i].end());

			for (int j = 0; j < result1[i].size(); j++) {
				if (result1[i].size() - 1 == j) {
					if (i == n - 1)
						printf("%d", result1[i][j]);
					else
						printf("%d\n", result1[i][j]);
				}
				else
					printf("%d ", result1[i][j]);
			}
		}
	}
	else
		printf("-1");
}