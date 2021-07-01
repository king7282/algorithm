#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

int degree[32010];
std::vector<int> graph[32010];
std::priority_queue<int, std::vector<int>, std::greater<int>> qu;

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		graph[a].push_back(b);
		degree[b]++;
	}

	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0)
			qu.push(i);
	}

	while (!qu.empty()) {
		int top = qu.top();
		qu.pop();
		printf("%d ", top);

		for (int i = 0; i < graph[top].size(); i++) {
			degree[graph[top][i]]--;
			if (degree[graph[top][i]] == 0)
				qu.push(graph[top][i]);
		}
	}
	
}
