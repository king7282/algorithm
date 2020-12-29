#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

int delay[1010], dp[1010];
std::vector<int> graph[1010];

int solve(int num) {
	if (dp[num] != -1)
		return dp[num];

	dp[num] = 0;
	for (int i = 0; i < graph[num].size(); i++)
		dp[num] = std::max(dp[num], solve(graph[num][i]));
	dp[num] += delay[num];

	return dp[num];
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n, k;
		scanf("%d %d", &n, &k);

		for (int i = 1; i <= n; i++)
			scanf("%d", delay + i);

		for (int i = 1; i <= k; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			graph[b].push_back(a);
		}

		int target;
		scanf("%d", &target);

		memset(dp, -1, sizeof(dp));
		printf("%d\n", solve(target));

		for (int i = 1; i <= n; i++)
			graph[i].clear();
	}
}