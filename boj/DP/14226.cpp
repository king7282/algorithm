#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int dp[2010][2010], goal;

int solve(int cur, int clip) {
	if (cur == goal)
		return 0;
	
	if (cur > goal * 2)
		return INT_MAX / 2;

	if (dp[cur][clip] != -1)
		return dp[cur][clip];

	dp[cur][clip] = INT_MAX / 2;
	if (clip != 0)
		dp[cur][clip] = std::min(dp[cur][clip], solve(cur + clip, clip) + 1);

	dp[cur][clip] = std::min(dp[cur][clip], solve(cur, cur) + 1);
	
	if (cur != 0)
		dp[cur][clip] = std::min(dp[cur][clip], solve(cur - 1, clip) + 1);
	return dp[cur][clip];
}

int main(void) {
	scanf("%d", &goal);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1, 0));
}