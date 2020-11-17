#include <stdio.h>
#include <algorithm>
#include <cstring>
 
int dp[5010][5010];
char input1[5010], input2[5010];
 
int func(int x, int y) {
	if (x == 0 || y == 0)
		return 0;
 
	if (dp[x][y] != -1)
		return dp[x][y];
 
	dp[x][y] = 0;
	if (input1[x] == input2[y]) {
		dp[x][y] = std::max(dp[x][y], func(x - 1, y - 1) + 2);
	}
	dp[x][y] = std::max(dp[x][y], func(x - 1, y) - 1);
	dp[x][y] = std::max(dp[x][y], func(x, y - 1) - 1);
 
	return dp[x][y];
}
 
int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= n; i++)
		scanf(" %c", input1 + i);
 
	for (int i = 1; i <= m; i++)
		scanf(" %c", input2 + i);
 
	memset(dp, -1, sizeof(dp));
	int result = 0;
 
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			result = std::max(result, func(i, j));
		}
	}
	printf("%d\n", result);
}