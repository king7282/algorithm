#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>

std::vector<int> graph[32010];
int degree[32010];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		degree[b]++;
	}

	std::queue<int> qu;

	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0)
			qu.push(i);
	}

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();

		printf("%d ", front);

		for (int i = 0; i < graph[front].size(); i++) {
			degree[graph[front][i]]--;
			if (degree[graph[front][i]] == 0)
				qu.push(graph[front][i]);
		}
	}


}