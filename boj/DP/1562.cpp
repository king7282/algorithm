#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000000

long long dp[110][10][1 << 10];
int n;

long long solve(int num, int cur, int bitmask) {
	if (num == n) {
		if (bitmask == (1 << 10) - 1)
			return 1;
		return 0;
	}

	if (dp[num][cur][bitmask] != -1)
		return dp[num][cur][bitmask];
	
	dp[num][cur][bitmask] = 0;

	if (cur != 0)
		dp[num][cur][bitmask] = (dp[num][cur][bitmask] + solve(num + 1, cur - 1, bitmask | (1 << (cur - 1)))) % MOD;

	if (cur != 9)
		dp[num][cur][bitmask] = (dp[num][cur][bitmask] + solve(num + 1, cur + 1, bitmask | (1 << (cur + 1)))) % MOD;

	return dp[num][cur][bitmask];
}

int main(void) {
	scanf("%d", &n);

	memset(dp, -1, sizeof(dp));
	long long result = 0;
	for (int i = 1; i <= 9; i++)
		result = (result + solve(1, i, 1 << i)) % MOD;

	printf("%lld\n", result);
}