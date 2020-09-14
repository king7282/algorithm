#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <climits>

struct info {
	int len;
	int bitmask;
};

long long dp[1 << 20];
std::vector<info> proofs[21];
int n;

long long func(int bitmask) {
	if ((bitmask & 1) != 0)
		return 0;

	if (dp[bitmask] != -1)
		return dp[bitmask];

	dp[bitmask] = LLONG_MAX / 2;
	for (int i = 0; i < n; i++) {
		if ((bitmask & (1 << i)) != 0)
			continue;

		for (int j = 0; j < proofs[i].size(); j++) {
			if ((bitmask & proofs[i][j].bitmask) == proofs[i][j].bitmask) {
				dp[bitmask] = std::min(dp[bitmask], func(bitmask | (1 << i)) + proofs[i][j].len);
			}
		}
	}

	return dp[bitmask];
}


int main(void) {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int q;
		scanf("%d", &q);

		for (int j = 0; j < q; j++) {
			proofs[i].push_back(info());
			scanf("%d", &proofs[i][j].len);
			int k;
			scanf("%d", &k);

			for (int a = 0; a < k; a++) {
				int tmp;
				scanf("%d", &tmp);
				proofs[i][j].bitmask |= (1 << tmp);
			}
		}
	}

	memset(dp, -1, sizeof(dp));
	printf("%lld\n", func(0));
}