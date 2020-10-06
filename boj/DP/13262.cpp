#include <stdio.h>
#include <algorithm>

int OR[5010][5010];
long long dp[5010][5010];

void func(int num, int s, int e, int p, int q) {
	if (s > e)
		return;

	int mid = (s + e) / 2, index = q;
	dp[mid][num] = -1;

	for (int i = std::min(mid, q); i >= p; i--) {
		long long tmp = dp[i - 1][num - 1] + OR[i][mid];
		if (tmp > dp[mid][num]) {
			dp[mid][num] = tmp;
			index = i;
		}
	}

	func(num, s, mid - 1, p, index);
	func(num, mid + 1, e, index, q);
}

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		for (int j = 1; j <= i; j++)
			OR[j][i] = (OR[j][i - 1] | a);
		dp[i][1] = OR[1][i];
	}

	for (int i = 2; i <= k; i++) {
		func(i, i, n, i, n);
	}
	printf("%lld\n", dp[n][k]);
}