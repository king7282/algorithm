#include <stdio.h>
#include <algorithm>
#include <vector>
#define MOD 998244353

std::vector<std::pair<long long, long long>> gcd[100010];
long long result[100010];

long long eexp(long long t, long long p) {
	if (p == 0)
		return 1;

	long long tmp = eexp(t, p / 2);
	tmp = (tmp * tmp) % MOD;
	if (p % 2 == 1)
		tmp = (tmp * t) % MOD;

	return tmp;
}

int main(void) {
	int n;
	long long max1 = 0;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		long long a, b;
		scanf("%I64d %I64d", &a, &b);
		max1 = std::max(max1, a);
		for (long long j = 1; j * j <= a; j++) {
			if (a % j == 0) {
				gcd[j].push_back(std::make_pair(a, b));
				if (j != a / j)
					gcd[a / j].push_back(std::make_pair(a, b));
			}
		}
	}

	for (long long i = max1; i >= 1; i--) {
		if (gcd[i].size() == 0)
			continue;

		long long k = 0, sum = 0;
		for (int j = 0; j < gcd[i].size(); j++) {
			k = k + gcd[i][j].second;
			sum = (sum + gcd[i][j].first * gcd[i][j].second % MOD) % MOD;
		}

		if (k == 1) {
			result[i] = 0;
		}
		else if (k == 2) {
			result[i] = (result[i] + sum * sum % MOD) % MOD;
		}else {
			long long tmp1 = 0, tmp2 = 0;
			long long k2 = eexp(2, k - 2), k3 = eexp(2, k - 3);

			for (int j = 0; j < gcd[i].size(); j++) {
				tmp1 = (tmp1 + ((((gcd[i][j].first * gcd[i][j].first) % MOD * gcd[i][j].second) % MOD * k2) % MOD * ((k - 1) % MOD)) % MOD) % MOD;
				long long ttmp = gcd[i][j].first * ((k3 * ((k - 2) % MOD) % MOD + k2) % MOD) % MOD;
				tmp2 = (tmp2 + (ttmp * (sum + MOD - gcd[i][j].first) % MOD) % MOD * gcd[i][j].second % MOD) % MOD;
			}

			result[i] = (result[i] + (tmp1 + tmp2) % MOD) % MOD;
		}

		if (i != 1) {
			for (long long j = 1; j * j <= i; j++) {
				if (i % j == 0) {
					result[j] = (result[j] + MOD - result[i]) % MOD;
					if (i / j != j && i / j != i)
						result[i / j] = (result[i / j] + MOD - result[i]) % MOD;
				}
			}
		}
	}

	printf("%I64u\n", result[1]);
}