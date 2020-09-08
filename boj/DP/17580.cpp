#include <stdio.h>
#include <algorithm>
#include <climits>
#include <cstring>

int n, m, input[1010], goals[1010];
int dp[1010][1010];

int func(int num, int cnt) {
	if (cnt > n || cnt < 0)
		return INT_MAX / 2;

	if (num == n + 1)
		return 0;

	if (dp[num][cnt] != -1)
		return dp[num][cnt];

	int cur = (goals[num] - input[num] + m) % m, next = (goals[num + 1] - input[num + 1] + m) % m;
	dp[num][cnt] = std::min(INT_MAX / 2, func(num, cnt + 1) + m);

	if (cur < next) {
		dp[num][cnt] = std::min(dp[num][cnt], func(num + 1, cnt) + (next - cur));
		dp[num][cnt] = std::min(dp[num][cnt], func(num + 1, cnt - 1));
	}
	else {
		dp[num][cnt] = std::min(dp[num][cnt], func(num + 1, cnt));
		dp[num][cnt] = std::min(dp[num][cnt], func(num + 1, cnt + 1) + (next + m - cur));
	}

	return dp[num][cnt];
}

int main(void) {
	while (1) {
		scanf("%d %d", &n, &m);

		if (n == 0 && m == 0)
			break;

		for (int i = 1; i <= n; i++) {
			scanf("%d", input + i);
		}

		for (int i = 1; i <= n; i++) {
			scanf("%d", goals + i);
		}

		memset(dp, -1, sizeof(dp));
		input[n + 1] = goals[n + 1] = 0;

		printf("%d\n", func(1, 0) + (goals[1] - input[1] + m) % m);
	}
}