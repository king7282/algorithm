#include <stdio.h>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

struct node {
	int next, prices, times;
	node(int next, int prices, int times) : next(next), prices(prices), times(times) {}
};

bool operator<(node a, node b) {
	return a.times > b.times;
}

int n, m, k;
std::vector<node> graph[110];
int visited[110][10010];

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		scanf("%d %d %d", &n, &m, &k);

		for (int i = 1; i <= k; i++) {
			int a, b, c, d;
			scanf("%d %d %d %d", &a, &b, &c, &d);

			graph[a].push_back(node(b, c, d));
		}

		std::priority_queue<node> qu;
		memset(visited, 0x7f, sizeof(visited));
		visited[1][0] = 0;
		qu.push(node(1, 0, 0));

		while (!qu.empty()) {
			node top = qu.top();
			qu.pop();

			if (visited[top.next][top.prices] != top.times)
				continue;

			for (int i = 0; i < graph[top.next].size(); i++) {
				int next = graph[top.next][i].next, prices = graph[top.next][i].prices + top.prices;

				if (prices > m)
					continue;

				if (visited[next][prices] > top.times + graph[top.next][i].times) {
					visited[next][prices] = top.times + graph[top.next][i].times;
					qu.push(node(next, prices, visited[next][prices]));
				}
			}
		}

		int result = INT_MAX / 2;

		for (int i = 0; i <= m; i++) {
			result = std::min(result, visited[n][i]);
		}

		if (result == INT_MAX / 2)
			printf("Poor KCM\n");
		else
			printf("%d\n", result);

		for (int i = 1; i <= n; i++)
			graph[i].clear();
	}
}