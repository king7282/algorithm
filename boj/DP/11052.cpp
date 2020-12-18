#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

long long input[1010], dp[1010][1010];

long long solve(int num, int x) {
	if (x == 0)
		return 0;

	if (x < 0 || num == 0)
		return INT_MIN / 2;

	if (dp[num][x] != -1)
		return dp[num][x];

	dp[num][x] = 0;
	for (int i = 0; i * num <= x; i++) {
		dp[num][x] = std::max(dp[num][x], solve(num - 1, x - i * num) + input[num] * i);
	}
	
	return dp[num][x];
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld", input + i);

	memset(dp, -1, sizeof(dp));
	printf("%lld\n", solve(n, n));
}