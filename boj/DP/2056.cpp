#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

int times[10010], dp[10010];
std::vector<int> graph[10010];

int solve(int num) {
	if (dp[num] != -1)
		return dp[num];

	int prev = 0;
	for (int i = 0; i < graph[num].size(); i++)
		prev = std::max(prev, solve(graph[num][i]));

	return dp[num] = prev + times[num];
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int k;
		scanf("%d %d", times + i, &k);

		for (int j = 0; j < k; j++) {
			int prev;
			scanf("%d", &prev);
			
			graph[i].push_back(prev);
		}
	}

	memset(dp, -1, sizeof(dp));
	int result = 0;
	for (int i = 1; i <= n; i++) {
		result = std::max(result, solve(i));
	}

	printf("%d\n", result);
}