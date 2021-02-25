#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>
#include <vector>

int n, m, money[310][21];
int dp[21][310];
std::pair<int, int> trace[21][310];
std::vector<int> result;

int solve(int corp, int num) {
	if (num < 0)
		return INT_MIN / 2;
	if (corp == m)
		return 0;

	if (dp[corp][num] != -1)
		return dp[corp][num];

	dp[corp][num] = solve(corp + 1, num);
	trace[corp][num] = { corp + 1, num };

	for (int i = 0; i < n; i++) {
		if (dp[corp][num] < solve(corp + 1, num - (i + 1)) + money[i][corp]) {
			dp[corp][num] = solve(corp + 1, num - (i + 1)) + money[i][corp];
			trace[corp][num] = { corp + 1, num - (i + 1) };
		}
	}

	return dp[corp][num];
}

void back(int corp, int num) {
	if (corp == m)
		return;

	result.push_back(num - trace[corp][num].second);
	back(trace[corp][num].first, trace[corp][num].second);
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		int tmp;
		scanf("%d", &tmp);

		for (int j = 0; j < m; j++)
			scanf("%d", &money[i][j]);
	}

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(0, n));

	back(0, n);
	for (int i = 0; i < result.size(); i++)
		printf("%d ", result[i]);

}