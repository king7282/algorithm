#include <stdio.h>
#include <algorithm>
#include <cstring>

long long dp[31];

int solve(int num) {
	if (num <= 1)
		return 1;

	if (dp[num] != -1)
		return dp[num];

	return dp[num] = solve(num - 1) + 2 * solve(num - 2);
}

int main(void) {
	int n;
	scanf("%d", &n);

	memset(dp, -1, sizeof(dp));

	long long result = 0;
	if (n % 2 == 0) {
		result = (solve(n) + solve((n - 2) / 2) * 2 + solve(n / 2)) / 2;
	}
	else {
		result = (solve(n) + solve(n / 2)) / 2;
	}

	printf("%lld\n", result);
}