#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <climits>
#include <queue>
#define SIZE 262144

std::vector<int> graph[200010];
int degree[200010], result[200010];
bool check[200010];

int main(void) {
	int n, m;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		while (1) {
			int input;
			scanf("%d", &input);
			if (input == 0)
				break;
			graph[i].push_back(input);
		}
	}

	memset(result, -1, sizeof(result));
	std::queue<int> qu;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		int input;
		scanf("%d", &input);
		qu.push(input);
		check[input] = true;
		result[input] = 0;
	}
	
	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();

		for (int i = 0; i < graph[front].size(); i++) {
			if (check[graph[front][i]] == true)
				continue;

			degree[graph[front][i]]++;
			if (degree[graph[front][i]] >= graph[graph[front][i]].size() / 2 + graph[graph[front][i]].size() % 2) {
				check[graph[front][i]] = true;
				result[graph[front][i]] = result[front] + 1;
				qu.push(graph[front][i]);
			}
		}
	}
	
	for (int i = 1; i <= n; i++)
		printf("%d ", result[i]);
}