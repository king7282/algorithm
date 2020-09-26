#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

int input[81], n, dp[81][81][3161], index1[81];
int cnt0, cnt1;

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

int func(int zeros, int ones, int num) {
	if (num < 0)
		return INT_MAX / 2;

	if (ones == 0)
		return zeros * (zeros - 1) / 2;

	if (dp[zeros][ones][num] != -1)
		return dp[zeros][ones][num];

	int p = index1[cnt1 - ones + 1];
	dp[zeros][ones][num] = INT_MAX / 2;

	for (int i = 0; i <= zeros; i++) {
		int cur = n - (ones + (zeros - i)) + 1;
		dp[zeros][ones][num] = std::min(dp[zeros][ones][num], func(zeros - i, ones - 1, num - aabs(p - cur)) + i * (i - 1) / 2);
	}

	return dp[zeros][ones][num];
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		if (input[i] == 0)
			cnt0++;
		else {
			cnt1++;
			index1[cnt1] = i;
		}
	}

	memset(dp, -1, sizeof(dp));
	for (int i = 0; i <= n * (n - 1) / 2; i++) {
		printf("%d ", cnt0 * (cnt0 - 1) / 2 - func(cnt0, cnt1, i));
	}
}