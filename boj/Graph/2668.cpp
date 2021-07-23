#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

std::vector<int> graph[110], reverse[110], group[110];
bool visited[110];
int cnt, number[110], scc[110], check[110];

void dfs(int cur) {
	visited[cur] = true;

	for (int i = 0; i < graph[cur].size(); i++)
		if (visited[graph[cur][i]] == false)
			dfs(graph[cur][i]);

	number[++cnt] = cur;
}

void reverse_dfs(int cur) {
	scc[cur] = cnt;
	group[cnt].push_back(cur);

	for (int i = 0; i < reverse[cur].size(); i++)
		if (scc[reverse[cur][i]] == 0)
			reverse_dfs(reverse[cur][i]);
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		graph[i].push_back(a);
		reverse[a].push_back(i);
	}

	for (int i = 1; i <= n; i++) {
		if (visited[i] == false) {
			dfs(i);
		}
	}

	cnt = 0;
	for (int i = n; i >= 1; i--) {
		if (scc[number[i]] == 0) {
			cnt++;
			reverse_dfs(number[i]);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			if (scc[i] != scc[graph[i][j]]) {
				check[scc[i]]++;
			}
		}
	}

	std::vector<int> result;
	for (int i = 1; i <= cnt; i++) {
		if (check[i] == 0) {
			for (int j = 0; j < group[i].size(); j++)
				result.push_back(group[i][j]);
		}
	}

	std::sort(result.begin(), result.end());
	printf("%d\n", result.size());
	for (int i = 0; i < result.size(); i++)
		printf("%d\n", result[i]);
}