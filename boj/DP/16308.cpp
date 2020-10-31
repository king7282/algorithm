#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000009

long long dp[5010], input[5010];
long long fac[5010], comb[5010][5010];

long long eexp(long long p, long long t) {
	if (t == 0)
		return 1;

	long long tmp = eexp(p, t / 2);
	tmp = (tmp * tmp) % MOD;
	if (t % 2 == 1)
		tmp = (tmp * p) % MOD;

	return tmp;
}

long long func(int num) {
	if (num == 0)
		return 1;

	if (num == 1)
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = comb[1][num];

	for (int i = 1; i <= num; i++) {
		dp[num] = (dp[num] - (comb[i + 1][num] * func(i - 1)) % MOD + MOD) % MOD;
	}

	return dp[num];
}

int main(void) {
	int n;
	scanf("%d", &n);

	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = (fac[i - 1] * i) % MOD;

	for (int i = 1; i <= n; i++)
		scanf("%lld", input + i);

	std::sort(input + 1, input + 1 + n);

	comb[n + 1][n] = 1;
	for (int s = 1; s <= n; s++) {
		comb[s][s - 1] = 1;
		int cnt = 0, prev = -1;
		long long under = 1;
		for (int e = s; e <= n; e++) {
			if (prev == input[e]) {
				cnt++;
			}
			else {
				under = (under * fac[cnt]) % MOD;
				cnt = 1;
			}

			comb[s][e] = (fac[e - s + 1] * eexp((under * fac[cnt]) % MOD, MOD - 2)) % MOD;
			prev = input[e];
		}
	}

	memset(dp, -1, sizeof(dp));
	printf("%lld\n", func(n));
}