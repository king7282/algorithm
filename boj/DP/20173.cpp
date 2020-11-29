#include <stdio.h>
#include <algorithm>
#include <cstring>

int dp[1000010][2][2], input[1000010];
int n;

int aabs(int num) {
	if (num < 0)
		return -1 * num;
	return num;
}

int func(int num, int f, int s) {
	if (num == n + 1)
		return 1;

	if (dp[num][f][s] != -1)
		return dp[num][f][s];

	dp[num][f][s] = 0;

	for (int i = 0; i < 2; i++) {
		if (num == n && i == 1)
			continue;

		for (int j = 0; j < 2; j++) {
			if (num == n && j == 1)
				continue;

			if (aabs(i + f - (j + s)) == input[num]) {
				dp[num][f][s] = std::max(dp[num][f][s], func(num + 1, (i + 1) % 2, (j + 1) % 2));
			}
		}
	}

	return dp[num][f][s];
}

int main(void) {
	bool flag = true;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		if (input[i] > 2)
			flag = false;
	}

	memset(dp, -1, sizeof(dp));

	if (flag && func(1, 0, 0))
		printf("YES\n");
	else
		printf("NO\n");
}