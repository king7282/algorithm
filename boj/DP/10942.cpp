#include <stdio.h>
#include <algorithm>
#include <cstring>

int input[2010], dp[2010][2010];

int solve(int s, int e) {
	if (s == e || s > e)
		return 1;
	
	if (dp[s][e] != -1)
		return dp[s][e];

	dp[s][e] = 0;
	if (input[s] == input[e])
		dp[s][e] = solve(s + 1, e - 1);

	return dp[s][e];
}

int main(void) {
	int n, m;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) 
		scanf("%d", input + i);

	scanf("%d", &m);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= m; i++) {
		int s, e;
		scanf("%d %d", &s, &e);

		printf("%d\n", solve(s, e));
	}
}
