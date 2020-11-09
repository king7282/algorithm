#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
#include <cassert>

struct info {
	int next, weight;
	info(int next, int weight) : next(next), weight(weight) {}
};

bool operator<(info a, info b) {
	return a.weight < b.weight;
}

std::vector<info> graph[510];
int prefer[510][510], D[510][510], S[510][510];

int main(void) {
	int m, n;
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &prefer[i][j]);
			if (prefer[i][j] == 0)
				prefer[i][j] = 1000010;
		}
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == j)
				continue;

			for (int k = 1; k <= n; k++) {
				if (prefer[k][i] < prefer[k][j])
					D[i][j]++;
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			if (D[i][j] > D[j][i])
				graph[i].push_back(info(j, D[i][j]));
		}
	}

	for (int i = 1; i <= m; i++) {
		S[i][i] = 501;
		std::priority_queue<info> qu;
		qu.push(info(i, S[i][i]));
		while (!qu.empty()) {
			info top = qu.top();
			qu.pop();
			if (top.weight < S[i][top.next])
				continue;

			for (int j = 0; j < graph[top.next].size(); j++) {
				if (S[i][graph[top.next][j].next] < graph[top.next][j].weight) {
					S[i][graph[top.next][j].next] = graph[top.next][j].weight;
					qu.push(info(graph[top.next][j].next, graph[top.next][j].weight));
				}
			}
		}
	}

	std::vector<int> tmp;

	for (int i = 1; i <= m; i++) {
		bool result = true;
		for (int j = 1; j <= m && result; j++) {
			if (i == j)
				continue;

			if (S[i][j] < S[j][i])
				result = false;
		}

		if (result)
			tmp.push_back(i);
	}

	for (int i = 0; i < tmp.size(); i++) {
		if (i == tmp.size() - 1)
			printf("%d", tmp[i]);
		else
			printf("%d ", tmp[i]);
	}
	printf("\n");
}