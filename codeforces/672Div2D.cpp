#include <stdio.h>
#include <algorithm>
#include <set>
#define MOD 998244353

std::multiset<int> set;
std::pair<int, int> input[300010];
long long fac[300010];

long long eexp(long long t, long long p) {
	if (p == 0)
		return 1;

	long long tmp = eexp(t, p / 2);
	tmp = tmp * tmp % MOD;
	if (p % 2 == 1)
		tmp = tmp * t % MOD;

	return tmp;
}

long long func(int f, int e) {
	if (f < e)
		return 0;
	
	long long result = fac[f];
	result = result * eexp(fac[e], MOD - 2) % MOD;
	result = result * eexp(fac[(f - e)], MOD - 2) % MOD;

	return result;
	
} 

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);
	fac[0] = 1;

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &input[i].first, &input[i].second);
		fac[i] = fac[i - 1] * (long long)i % MOD;
	}

	std::sort(input + 1, input + 1 + n, [](std::pair<int, int> a, std::pair<int, int> b) {
		if (a.first == b.first)
			return a.second > b.second;
		return a.first < b.first;
	});

	long long result = 0;
	for (int i = 1; i <= n; i++) {
		while (set.size() > 0 && *set.begin() < input[i].first) {
			result = (result + func(set.size() - 1, k - 1)) % MOD;
			set.erase(set.begin());
		}

		set.insert(input[i].second);
	}

	result = (result + func(set.size(), k)) % MOD;
	printf("%I64d\n", result);

}