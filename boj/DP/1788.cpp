#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000000

int dp[1000010];

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

int main(void) {
	int n;
	scanf("%d", &n);
	if (n == 0) {
		printf("0\n0\n");
		return 0;
	}
	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2; i <= aabs(n); i++)
		dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;

	if(n >= 0)
		printf("1\n%d\n", dp[n]);
	else {
		if (aabs(n) % 2 == 0) {
			printf("-1\n");
		}
		else
			printf("1\n");
		printf("%d\n", dp[aabs(n)]);
	}
}