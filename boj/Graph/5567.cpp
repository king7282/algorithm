#include <stdio.h>
#include <vector>
#include <cstring>
#include <queue>

std::vector<int> graph[510];
int visited[510];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	memset(visited, -1, sizeof(visited));

	visited[1] = 0;
	std::queue<int> qu;

	qu.push(1);

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();

		for (int i = 0; i < graph[front].size(); i++) {
			if (visited[graph[front][i]] == -1) {
				visited[graph[front][i]] = visited[front] + 1;
				qu.push(graph[front][i]);
			}
		}
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (visited[i] != -1 && visited[i] <= 2)
			cnt++;
	}
	printf("%d\n", cnt - 1);
}