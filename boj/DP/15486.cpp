#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

long long dp[1500010], n;
std::pair<long long, long long> input[1500010];

long long solve(int num) {
	if (num == n + 1)
		return 0;

	if (num > n + 1)
		return LLONG_MIN / 2;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = std::max(solve(num + 1), solve(num + input[num].first) + input[num].second);
	return dp[num];
}

int main(void) {
	scanf("%lld", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld %lld", &input[i].first, &input[i].second);

	memset(dp, -1, sizeof(dp));
	printf("%lld\n", solve(1));
}