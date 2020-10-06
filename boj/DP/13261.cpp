#include <stdio.h>
#include <algorithm>
#include <climits>

long long input[8010], dp[8010][810], sum[8010];

void func(int g, int s, int e, int p, int q) {
	if (s > e)
		return;

	int mid = (s + e) / 2, index = q;
	dp[mid][g] = LLONG_MAX / 2;

	for (int i = p; i <= q && i <= mid; i++) {
		long long tmp = dp[i - 1][g - 1] + ((long long)mid - i + 1) * (sum[mid] - sum[i - 1]);
		if (dp[mid][g] > tmp) {
			dp[mid][g] = tmp;
			index = i;
		}
	}

	if (dp[mid][g] == LLONG_MAX / 2)
		while (1);

	func(g, s, mid - 1, p, index);
	func(g, mid + 1, e, index, q);
}
int main(void) {
	int l, g;
	scanf("%d %d", &l, &g);

	for (int i = 1; i <= l; i++) {
		scanf("%lld", input + i);
		sum[i] = sum[i - 1] + input[i];
		dp[i][1] = sum[i] * (long long)i;
	}

	long long result = LLONG_MAX / 2;
	for (int i = 2; i <= std::min(g, l); i++) {
		func(i, i, l, i, l);
		result = std::min(result, dp[l][i]);
	}

	printf("%lld\n", result);
}