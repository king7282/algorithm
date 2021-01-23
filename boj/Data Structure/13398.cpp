#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

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

	void update(int index, int s, int e, int i, int j, T v) {
		if (i > j || i > e || j < s)
			return;

		if (i <= s && e <= j)
			tree[index] = v;
		else {
			update(index * 2, s, (s + e) / 2, i, j, v);
			update(index * 2 + 1, (s + e) / 2 + 1, e, i, j, v);

			tree[index] = compar(tree[index * 2], tree[index * 2 + 1]);
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

	info(long long lsum = LLONG_MIN / 2, long long rsum = LLONG_MIN / 2, long long maxsum = LLONG_MIN / 2, long long sum = LLONG_MIN / 2) : lsum(lsum), rsum(rsum), maxsum(maxsum), sum(sum) {}
};

long long input[100010];

info compar(info a, info b) {
	info result;
	if (a.maxsum == LLONG_MIN / 2) {
		result = b;
	}
	else if (b.maxsum == LLONG_MIN / 2) {
		result = a;
	}
	else {
		result.sum = a.sum + b.sum;
		result.maxsum = std::max(a.maxsum, b.maxsum);
		result.maxsum = std::max(result.maxsum, a.rsum + b.lsum);
		result.lsum = std::max(a.lsum, a.sum + b.lsum);
		result.rsum = std::max(b.rsum, b.sum + a.rsum);
	}

	return result;
}

int main(void) {
	int n;
	scanf("%d", &n);

	long long result = LLONG_MIN / 2;
	segment_tree<info> tree(n + 1, compar, info(LLONG_MIN / 2, LLONG_MIN / 2, LLONG_MIN / 2, LLONG_MIN / 2));

	for (int i = 0; i < n; i++) {
		scanf("%lld", input + i);
		tree.init_value[i] = info(input[i], input[i], input[i], input[i]);
		result = std::max(result, input[i]);
	}

	if (result < 0) {
		printf("%lld\n", result);
		return 0;
	}

	tree.init(1, 0, n - 1);
	result = std::max(result, tree.query(1, 0, n - 1, 0, n - 1).maxsum);
	for (int i = 0; i < n; i++) {
		tree.update(1, 0, n - 1, i, i, info(0, 0, 0, 0));
		result = std::max(result, tree.query(1, 0, n - 1, 0, n - 1).maxsum);
		tree.update(1, 0, n - 1, i, i, info(input[i], input[i], input[i], input[i]));
	}

	printf("%lld\n", result);
		
}