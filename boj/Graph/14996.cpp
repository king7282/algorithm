#include <stdio.h>
#include <vector>
#include <queue>

std::vector<int> graph[50010], reverse[50010];
bool enemy[50010], visits[50010];
std::queue<int> qu;
int cnt, number, scc[50010], scc2[50010], indegree[50010];

void dfs(int num) {
	visits[num] = true;
	for (int i = 0; i < graph[num].size(); i++) {
		if (enemy[graph[num][i]] == false && visits[graph[num][i]] == false)
			dfs(graph[num][i]);
	}

	cnt++;
	scc[cnt] = num;
}

void rdfs(int num) {
	scc2[num] = number;
	for (int i = 0; i < reverse[num].size(); i++) {
		if (enemy[reverse[num][i]] == false && scc2[reverse[num][i]] == 0)
			rdfs(reverse[num][i]);
	}
}

int main(void) {
	int n, e, m;
	int result = 0;
	scanf("%d %d %d", &n, &e, &m);

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a == b)
			continue;
		graph[a].push_back(b);
		reverse[b].push_back(a);
	}

	for (int i = 0; i < e; i++) {
		int a;
		scanf("%d", &a);
		if (a < n && enemy[a] == false) {
			enemy[a] = true;
			qu.push(a);
			cnt++;
		}
	}

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();
		result++;
		for (int i = 0; i < reverse[front].size(); i++) {
			if (enemy[reverse[front][i]] == false) {
				enemy[reverse[front][i]] = true;
				qu.push(reverse[front][i]);
			}
		}
	}

	result -= cnt;
	cnt = 0;

	for (int i = 0; i < n; i++) {
		if (enemy[i] == false && visits[i] == false) {
			dfs(i);
		}
	}

	for (int i = cnt; i >= 1; i--) {
		if (enemy[scc[i]] == false && scc2[scc[i]] == 0) {
			number++;
			rdfs(scc[i]);
		}
	}

	for (int i = 0; i < n; i++) {
		if (enemy[i] == true || scc2[i] == 0)
			continue;

		for (int j = 0; j < graph[i].size(); j++) {
			if(scc2[i] != scc2[graph[i][j]] && scc2[graph[i][j]] != 0)
				indegree[scc2[graph[i][j]]]++;				
		}
	}

	for (int i = 1; i <= number; i++) {
		if (indegree[i] == 0)
			result++;
	}

	printf("%d\n", result);
}