#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

std::vector<std::pair<int, int>> graph[110];
std::pair<int, int> input[110];
bool visited[110];

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n + 2; i++) {
			scanf("%d %d", &input[i].first, &input[i].second);

			for (int j = 1; j < i; j++) {
				graph[i].push_back({ j, aabs(input[i].first - input[j].first) + aabs(input[i].second - input[j].second) });
				graph[j].push_back({ i, aabs(input[i].first - input[j].first) + aabs(input[i].second - input[j].second) });
			}
		}

		std::queue<int> qu;
		memset(visited, false, sizeof(visited));
		visited[1] = true;
		qu.push(1);

		while (!qu.empty()) {
			int front = qu.front();
			qu.pop();

			for (int i = 0; i < graph[front].size(); i++) {
				if (visited[graph[front][i].first] == true || graph[front][i].second > 1000)
					continue;

				visited[graph[front][i].first] = true;
				qu.push(graph[front][i].first);
			}
		}

		if (visited[n + 2] == true)
			printf("happy\n");
		else
			printf("sad\n");

		for (int i = 1; i <= n + 2; i++)
			graph[i].clear();
	}
}