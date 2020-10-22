#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>
#include <assert.h>

template <typename T>
struct segment_tree {
	std::vector<T> tree;
	T(*compar)(T, T);
	std::vector<T> init_value;
	T value;

	segment_tree(int _N, T(*_compar)(T, T), T _value) {
		int size = 1;
		while (size < _N)
			size *= 2;

		tree.resize(size * 4 + 1);
		init_value.resize(_N + 1);
		compar = _compar;
		value = _value;
	}

	void init(int node, int start, int end) {
		if (start == end)
			tree[node] = init_value[start];
		else {
			init(node << 1, start, (start + end) >> 1);
			init((node << 1) | 1, ((start + end) >> 1) + 1, end);
			tree[node] = compar(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	T query(int index, int s, int e, int i, int j) {
		if (i > j || i > e || j < s)
			return value;
		if (i <= s && e <= j)
			return tree[index];
		return compar(query(index * 2, s, (s + e) / 2, i, j), query(index * 2 + 1, (s + e) / 2 + 1, e, i, j));
	}

};

struct info {
	long long lsum, rsum;
	long long maxsum, sum;

	info(long long lsum = 0, long long rsum = 0, long long maxsum = 0, long long sum = 0) : lsum(lsum), rsum(rsum), maxsum(maxsum), sum(sum) {}
};

long long input[100010], sum[100010];

long long compar1(long long a, long long b) {
	return std::max(a, b);
}
long long compar2(long long a, long long b) {
	return std::min(a, b);
}

info compar3(info a, info b) {
	info result;

	result.sum = a.sum + b.sum;
	result.maxsum = std::max(a.maxsum, b.maxsum);
	result.maxsum = std::max(result.maxsum, a.rsum + b.lsum);
	result.maxsum = std::max(result.maxsum, a.sum + b.sum);
	result.lsum = std::max(a.lsum, a.sum + b.lsum);
	result.rsum = std::max(b.rsum, b.sum + a.rsum);

	return result;
}

int main(void) {
	int n;
	scanf("%d", &n);
	segment_tree<long long> upper(n + 1, compar1, LLONG_MIN / 2);
	segment_tree<long long> lower(n + 1, compar2, LLONG_MAX / 2);
	segment_tree<info> tree(n + 1, compar3, info(0, 0, 0, 0));

	lower.init_value[0] = 0;

	for (int i = 1; i <= n; i++) {
		scanf("%lld", input + i);
		sum[i] = sum[i - 1] + input[i];
		lower.init_value[i] = upper.init_value[i] = sum[i];
		tree.init_value[i] = info(input[i], input[i], input[i], input[i]);
	}

	upper.init(1, 1, n);
	lower.init(1, 0, n);
	tree.init(1, 1, n);

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &x2, &y1, &y2);

		if (x2 <= y1) {
			printf("%lld\n", upper.query(1, 1, n, y1, y2) - lower.query(1, 0, n, x1 - 1, x2 - 1));
		}
		else {
			long long result = LLONG_MIN / 2;
		
			result = std::max(result, upper.query(1, 1, n, y1, y2) - lower.query(1, 0, n, x1 - 1, y1 - 1));
			result = std::max(result, tree.query(1, 1, n, y1, x2).maxsum);
			result = std::max(result, upper.query(1, 1, n, x2, y2) - lower.query(1, 0, n, x1 - 1, x2 - 1));

			printf("%lld\n", result);
		}
	}
}