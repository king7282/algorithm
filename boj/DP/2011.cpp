#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000

char input[5010];
int dp[5010];
int n;

int solve(int num) {
	if (num == n)
		return 1;

	if (dp[num] != -1)
		return dp[num];
	
	dp[num] = 0;

	if(input[num] != '0')
		dp[num] = solve(num + 1);
	
	if (num < n - 1) {
		int next = (input[num] - '0') * 10 + input[num + 1] - '0';
		if (10 <= next && next <= 26)
			dp[num] = (dp[num] + solve(num + 2)) % MOD;
	}

	return dp[num];
}

int main(void) {
	scanf("%s", input);
	n = strlen(input);

	bool flag = false;
	for (int i = 0; i < n && !flag; i++) {
		if (!('0' <= input[i] && input[i] <= '9'))
			flag = true;
	}

	if (flag || n == 0)
		printf("0\n");
	else {
		memset(dp, -1, sizeof(dp));
		printf("%d\n", solve(0));
	}
}