#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int dp[110][110], n;
std::pair<int, int> persons[110];

int solve(int num, int hp) {
	if (hp <= 0)
		return INT_MIN / 2;

	if (num == n + 1)
		return 0;

	if (dp[num][hp] != -1)
		return dp[num][hp];

	dp[num][hp] = std::max(solve(num + 1, hp), solve(num + 1, hp - persons[num].first) + persons[num].second);

	return dp[num][hp];
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &persons[i].first);

	for (int i = 1; i <= n; i++)
		scanf("%d", &persons[i].second);

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1, 100));
}