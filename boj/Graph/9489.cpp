#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

int input[1010], depth[1010], goals, n, k, parent[1010];
std::vector<int> graph[1000010];

void dfs(int num, int cnt) {
	if (num == k)
		goals = cnt;

	depth[cnt]++;

	for (int i = 0; i < graph[num].size(); i++)
		dfs(graph[num][i], cnt + 1);
}

int main(void) {
	graph[0].push_back(1);
	while (1) {
		scanf("%d %d", &n, &k);
		if (n == 0 && k == 0)
			break;

		scanf("%d", input + 1);
		int cur = 0;
		if (k == input[1])
			k = 1;

		for (int i = 2; i <= n; i++) {
			scanf("%d", input + i);
			if (input[i] == k)
				k = i;

			if (input[i - 1] + 1 != input[i]) {
				cur++;
			}

			graph[cur].push_back(i);
			parent[i] = cur;
		}

		memset(depth, 0, sizeof(depth));
		dfs(parent[parent[k]], 0);

		int tmp = depth[goals];
		memset(depth, 0, sizeof(depth));
		dfs(parent[k], 0);
		printf("%d\n", tmp - depth[goals]);

		for (int i = 1; i <= n; i++)
			graph[i].clear();
	}
}