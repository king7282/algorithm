#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int input[110], dp[110][1010];
int n, limits;

int solve(int num, int cur) {
	if (cur < 0 || cur > limits)
		return INT_MIN / 2;
	if (num == n + 1)
		return cur;

	if (dp[num][cur] != -1)
		return dp[num][cur];

	dp[num][cur] = std::max(solve(num + 1, cur - input[num]), solve(num + 1, cur + input[num]));

	return dp[num][cur];
}
int main(void) {
	int start;
	scanf("%d %d %d", &n, &start, &limits);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	memset(dp, -1, sizeof(dp));
	if (solve(1, start) == INT_MIN / 2)
		printf("-1\n");
	else
		printf("%d\n", solve(1, start));
}