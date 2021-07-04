#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstring>

std::vector<int> graph[10010], reverse[10010], scc_graph[10010];
bool visited[10010];
int cnt, number[10010], scc_number[10010], in[10010], degree[10010];

void scc(int cur) {
	visited[cur] = true;

	for (int i = 0; i < graph[cur].size(); i++)
		if (visited[graph[cur][i]] == false)
			scc(graph[cur][i]);

	cnt++;
	number[cnt] = cur;
}

void scc_reverse(int cur) {
	visited[cur] = true;
	scc_number[cur] = cnt;
	in[cnt]++;

	for (int i = 0; i < reverse[cur].size(); i++)
		if (visited[reverse[cur][i]] == false)
			scc_reverse(reverse[cur][i]);
}

int solve(int num) {
	visited[num] = true;
	int result = in[num];

	for (int i = 0; i < scc_graph[num].size(); i++) {
		if (visited[scc_graph[num][i]] == false)
			result += solve(scc_graph[num][i]);
	}

	return result;
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		reverse[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 1; i <= n; i++) {
		if (visited[i] == false) {
			scc(i);
		}
	}

	cnt = 0;
	memset(visited, false, sizeof(visited));
	for (int i = n; i >= 1; i--) {
		if (visited[number[i]] == false) {
			cnt++;
			scc_reverse(number[i]);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			if (scc_number[i] != scc_number[graph[i][j]]) {
				scc_graph[scc_number[i]].push_back(scc_number[graph[i][j]]);
				degree[scc_number[graph[i][j]]]++;
			}
		}

	}

	for (int i = 1; i <= cnt; i++) {
		std::sort(scc_graph[i].begin(), scc_graph[i].end());
		scc_graph[i].erase(std::unique(scc_graph[i].begin(), scc_graph[i].end()), scc_graph[i].end());
	}

	std::vector<int> result;
	int max_nodes = 0;

	for (int i = 1; i <= cnt; i++) {
		if (degree[i] == 0) {
			memset(visited, false, sizeof(visited));
			int tmp = solve(i);
			if (tmp > max_nodes) {
				max_nodes = tmp;
				result.clear();
				result.push_back(i);
			}
			else if (tmp == max_nodes)
				result.push_back(i);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		bool flag = false;
		for (int j = 0; j < result.size() && !flag; j++) {
			if (result[j] == scc_number[i])
				flag = true;
		}

		if (flag)
			printf("%d ", i);
	}
}