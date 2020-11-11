#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <climits>
#include <cstring>
#include <cassert>
#define SIZE 262144

long long sum[250010];
int n, k, zero, indexs[SIZE], tmp[SIZE];
std::vector<long long> X;

class FenwickTree {
public:
	int size;
	std::vector<int> arr;
	std::vector<int> data;

	FenwickTree(int _N) {
		size = _N;
		arr.resize(size + 1);
		data.resize(size + 1);
	}

	void update(int x, int val) {
		int delta_val = val - arr[x];
		arr[x] = val;

		while (x <= size) {
			data[x] += delta_val;
			x += (x&-x);
		}
	}
	int sum(int x) {
		int ret = 0;
		while (x) {
			ret += data[x];
			x &= x - 1;
		}
		return ret;
	}
	int sum(int x, int y) {
		return sum(y) - sum(x - 1);
	}
};

int func(long long num) {
	FenwickTree tree(X.size() + 1);
	memset(tmp, 0, sizeof(tmp));

	int result = 0;
	tree.update(zero + 1, 1);
	tmp[zero] = 1;
	for (int i = 1; i <= n; i++) {
		int goal = std::lower_bound(X.begin(), X.end(), sum[i] - num) - X.begin();
		if(goal > 0)
			result += tree.sum(goal);
		if (result >= k)
			return result;
		tmp[indexs[i]]++;
		tree.update(indexs[i] + 1, tmp[indexs[i]]);
	}

	return result;
}

int main(void) {
	long long max1 = 0, min1 = 0, s = LLONG_MAX / 2, e = LLONG_MIN / 2;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		sum[i] = sum[i - 1] + a;
		X.push_back(sum[i]);
		s = std::min(s, sum[i] - max1);
		e = std::max(e, sum[i] - min1);

		max1 = std::max(max1, sum[i]);
		min1 = std::min(min1, sum[i]);

	}

	X.push_back(0);
	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	for (int i = 1; i <= n; i++)
		indexs[i] = std::lower_bound(X.begin(), X.end(), sum[i]) - X.begin();
	zero = std::lower_bound(X.begin(), X.end(), 0) - X.begin();

	long long r = e;

	while (s <= e) {
		long long mid = (s + e) / 2;

		if (func(mid) < k) {
			e = mid - 1;
			r = std::min(r, mid);
		}
		else
			s = mid + 1;
	}

	std::vector<long long> result;
	int f = k - func(r);
	for (int i = 0; i < f; i++) {
		result.push_back(r);
	}

	std::multiset<long long> set;
	set.insert(0);
	for (int i = 1; i <= n; i++) {
		auto finish = set.lower_bound(sum[i] - r);
		for (auto it = set.begin(); it != finish; it++)
			result.push_back(sum[i] - *it);
		set.insert(sum[i]);
	}

	std::sort(result.rbegin(), result.rend());
	for (int i = 0; i < result.size(); i++)
		printf("%lld ", result[i]);
	printf("\n");
}