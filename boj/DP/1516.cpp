#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>

int dp[510], input[510];
std::vector<int> graph[510];

int solve(int num) {
	if (dp[num] != -1)
		return dp[num];

	dp[num] = 0;
	for (int i = 0; i < graph[num].size(); i++) {
		dp[num] = std::max(dp[num], solve(graph[num][i]));
	}

	return dp[num] = dp[num] + input[num];
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);

		while (1) {
			int tmp;
			scanf("%d", &tmp);

			if (tmp == -1)
				break;

			graph[i].push_back(tmp);
		}
	}

	memset(dp, -1, sizeof(dp));

	for (int i = 1; i <= n; i++) {
		printf("%d\n", solve(i));
	}
}