#include <stdio.h>
#include <algorithm>
#include <cstring>

int dp[110][110][110];

int solve(int a, int b, int c) {
	if (dp[a][b][c] != -1)
		return dp[a][b][c];

	dp[a][b][c] = 0;

	for (int i = a + 1; i < b; i++) {
		dp[a][b][c] = std::max(dp[a][b][c], solve(a, i, b) + 1);
	}

	for (int i = b + 1; i < c; i++) {
		dp[a][b][c] = std::max(dp[a][b][c], solve(b, i, c) + 1);
	}

	return dp[a][b][c];
}

int main(void) {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	
	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(a, b, c));
}