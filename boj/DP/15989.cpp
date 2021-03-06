#include <stdio.h>
#include <cstring>
#include <algorithm>

long long dp[10010][4];

long long solve(int num, int plus) {
	if (num < 0)
		return 0;

	if (num == 0)
		return 1;

	if (plus == 1)
		return 1;

	if (dp[num][plus] != -1)
		return dp[num][plus];

	dp[num][plus] = solve(num, plus - 1) + solve(num - plus, plus);


	return dp[num][plus];
}
int main(void) {
	int test;
	scanf("%d", &test);

	memset(dp, -1, sizeof(dp));

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);

		printf("%lld\n", solve(n, 3));
	}
}