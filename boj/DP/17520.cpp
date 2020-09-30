#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 16769023

int dp[100010][3], n;

long long func(int num, int flag) {
	if (num == n)
		return 1;

	if (dp[num][flag] != -1)
		return dp[num][flag];

	dp[num][flag] = 0;
	if (flag == 0) {
		dp[num][flag] = func(num + 1, flag + 1) % MOD;
	}
	else if (flag == 1) {
		dp[num][flag] = (func(num + 1, flag - 1) + func(num + 1, flag + 1)) % MOD;
	}
	else if (flag == 2) {
		dp[num][flag] = func(num + 1, flag - 1) % MOD;
	}

	return dp[num][flag];
}
int main(void) {
	scanf("%d", &n);
	
	memset(dp, -1, sizeof(dp));
	printf("%lld\n", func(0, 1));
}