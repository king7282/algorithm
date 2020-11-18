#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

struct info {
	int next, weights;
	info(int next, int weights) : next(next), weights(weights) {}
};

bool operator<(info a, info b) {
	return a.weights > b.weights;
}

std::vector<int> graph[100010];
int weights[100010], visits[100010];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);

		weights[a]++;
		weights[b]++;
	}

	if (n <= 2) {
		printf("1\n");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		graph[n].push_back(i);
	}

	std::priority_queue<info> qu;
	qu.push(info(n, 0));
	while (!qu.empty()) {
		info top = qu.top();
		qu.pop();

		if (visits[top.next] != top.weights)
			continue;

		for (int i = 0; i < graph[top.next].size(); i++) {
			if (weights[top.next] >= weights[graph[top.next][i]])
				continue;

			if (visits[graph[top.next][i]] < top.weights + 1) {
				visits[graph[top.next][i]] = top.weights + 1;
				qu.push(info(graph[top.next][i], top.weights + 1));
			}
		}
	}

	int result = 0;
	for (int i = 0; i < n; i++) {
		result = std::max(result, visits[i]);
	}
	printf("%d\n", result);
}