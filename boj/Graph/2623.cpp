#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

std::vector<int> graph[1010], result;
int degree[1010];

int main(void) {
	int n, m;
	
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int k;
		scanf("%d", &k);

		int prev = 0;
		for (int j = 1; j <= k; j++) {
			int a;
			scanf("%d", &a);
			if (prev != 0) {
				graph[prev].push_back(a);
				degree[a]++;
			}
			prev = a;
		}
	}
	
	std::queue<int> qu;
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0)
			qu.push(i);
	}

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();
		result.push_back(front);

		for (int i = 0; i < graph[front].size(); i++) {
			degree[graph[front][i]]--;
			if (degree[graph[front][i]] == 0)
				qu.push(graph[front][i]);
		}
	}

	if (result.size() != n) {
		printf("0\n");
	}
	else {
		for (int i = 0; i < result.size(); i++)
			printf("%d\n", result[i]);
	}

}