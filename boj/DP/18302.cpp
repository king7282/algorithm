#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>
#define MOD 1000000007
#define SIZE 1048576

long long fac[SIZE * 2];
int input[SIZE], tree[SIZE * 2 + 1], n;
std::vector<std::vector<int>> indexs;

void update(int num, int val) {
	num |= SIZE;
	tree[num] = val;
	while (num >>= 1)
		tree[num] = std::min(tree[num << 1], tree[num << 1 | 1]);
}

int query(int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = INT_MAX / 2;

	while (s <= e) {
		if (s % 2 == 1) r = std::min(r, tree[s]);
		if (e % 2 == 0) r = std::min(r, tree[e]);

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

long long eexp(long long t, long long p) {
	if (p == 0)
		return 1;

	long long tmp = eexp(t, p / 2);
	tmp = (tmp * tmp) % MOD;
	if (p % 2 == 1)
		tmp = (tmp * t) % MOD;

	return tmp;
}

long long func(int s, int e) {
	if (s == e)
		return 1;

	int num = query(s, e);
	int tmps = 0, tmpe = indexs[num].size() - 1, r = indexs[num].size() - 1;

	while (tmps <= tmpe) {
		int mid = (tmps + tmpe) / 2;
		if (indexs[num][mid] >= s) {
			tmpe = mid - 1;
			r = std::min(r, mid);
		}
		else
			tmps = mid + 1;
	}

	long long result = 1;
	int prev = s, cnt = 0;
	for (int i = r; i < indexs[num].size() && indexs[num][i] <= e; i++) {
		cnt++;
		if (prev < indexs[num][i])
			result = (result * func(prev, indexs[num][i] - 1)) % MOD;
		prev = indexs[num][i] + 1;
	}

	if (prev < e)
		result = (result * func(prev, e)) % MOD;

	long long tmp = eexp(fac[cnt], MOD - 2);

	result = (result * fac[2 * cnt]) % MOD;
	result = (result * tmp) % MOD;
	result = (result * tmp) % MOD;
	result = (result * eexp(cnt + 1, MOD - 2)) % MOD;
	return result;
}

int main(void) {
	scanf("%d", &n);
	std::vector<int> X;
	memset(tree, 0x7f, sizeof(tree));
	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		X.push_back(input[i]);
	}

	if (n == 0) {
		printf("1\n");
		return 0;
	}
	if (n == 1) {
		printf("1\n");
		return 0;
	}
	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	indexs.resize(X.size());
	for (int i = 1; i <= n; i++) {
		input[i] = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
		indexs[input[i]].push_back(i);
		update(i, input[i]);
	}

	fac[0] = 1;
	for (long long i = 1; i <= 2 * n; i++) {
		fac[i] = (fac[i - 1] * i) % MOD;
	}

	printf("%lld\n", func(1, n));
}