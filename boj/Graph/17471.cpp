#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>

std::vector<int> graph[10];
bool visited[10], color[10];
int n, people[10];

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

void dfs(int cur) {
	visited[cur] = true;

	for (int i = 0; i < graph[cur].size(); i++) {
		if (visited[graph[cur][i]] == false && color[cur] == color[graph[cur][i]])
			dfs(graph[cur][i]);
	}
}

int main(void) {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", people + i);
	}

	for (int i = 0; i < n; i++) {
		int k;
		scanf("%d", &k);

		for (int j = 0; j < k; j++) {
			int a;
			scanf("%d", &a);
			a--;

			graph[i].push_back(a);
		}
	}

	int result = INT_MAX / 2;
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if ((i & (1 << j)) == 0)
				color[j] = 0;
			else
				color[j] = 1;
		}
		
		memset(visited, false, sizeof(visited));
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			if (visited[j] == false) {
				cnt++;
				dfs(j);
			}
		}

		if (cnt == 2) {
			int tmp = 0;

			for (int j = 0; j < n; j++) {
				if (color[j] == 0)
					tmp += people[j];
				else
					tmp -= people[j];
			}

			result = std::min(result, aabs(tmp));
		}
	}

	if (result == INT_MAX / 2)
		printf("-1\n");
	else
		printf("%d\n", result);
}