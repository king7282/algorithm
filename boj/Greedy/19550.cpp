#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>

struct segment_tree {
	std::vector<int> lazy, tree;
	int(*compar)(int, int);
	int value;

	segment_tree(int _N, int (*_compar)(int ,int), int _value) {
		int size = 1;
		while (size < _N)
			size *= 2;

		value = _value;
		lazy.resize(size * 2 + 1, value);
		tree.resize(size * 2 + 1, value);
		compar = _compar;
	}

	void lazy_propagation(int node, int start, int end) {
		if (lazy[node] != value) {
			tree[node] = compar(tree[node], lazy[node]);
			if (start != end) {
				lazy[node << 1] = compar(lazy[node << 1], lazy[node]);
				lazy[(node << 1) | 1] = compar(lazy[node << 1], lazy[node]);
			}
			lazy[node] = value;
		}
	}

	void update(int node, int start, int end, int i, int j, int val) {
		lazy_propagation(node, start, end);
		if (i > end || j < start)
			return;
		if (i <= start && end <= j) {
			tree[node] = compar(tree[node], val);
			if (start != end) {
				lazy[node << 1] = compar(lazy[node << 1], val);
				lazy[(node << 1) | 1] = compar(lazy[(node << 1) | 1], val);
			}
			return;
		}
		else {
			update(node << 1, start, (start + end) / 2, i, j, val);
			update((node << 1) | 1, (start + end) / 2 + 1, end, i, j, val);
			tree[node] = compar(tree[node << 1], tree[(node << 1) | 1]);
		}
	}

	int query(int node, int start, int end, int i, int j) {
		lazy_propagation(node, start, end);
		if (i > end || j < start)
			return value;
		if (i <= start && end <= j)
			return tree[node];
		return compar(query(node * 2, start, (start + end) / 2, i, j), query(node * 2 + 1, (start + end) / 2 + 1, end, i, j));
	}
};

struct info {
	long long x, y;
	info(long long x, long long y) : x(x), y(y) {}
};

std::vector<info> input;
int next[400010], sparse[400010][25];
bool check[400010];

int compar1(int a, int b) {
	return std::min(a, b);
}

int compar2(int a, int b) {
	return std::max(a, b);
}

int main(void) {
	int n;
	long long l;
	scanf("%d %lld", &n, &l);
	
	std::vector<long long> X;
	for (int i = 1; i <= n; i++) {
		long long a, b;
		scanf("%lld %lld", &a, &b);

		if (a <= b) {
			if (b - a > l / 2) {
				input.push_back(info(b, a + l));
				input.push_back(info(b + l, 2 * l - 1));
			}
			else {
				input.push_back(info(a, b));
				input.push_back(info(a + l, b + l));
			}
		}
		else {
			if (a - b > l / 2) {
				input.push_back(info(a, b + l));
				input.push_back(info(a + l, 2 * l - 1));
			}
			else {
				input.push_back(info(b, a));
				input.push_back(info(b + l, a + l));
			}
		}
	}

	std::sort(input.begin(), input.end(), [](info a, info b) {
		if (a.y == b.y)
			return a.x > b.x;
		return a.y < b.y;
	});

	std::set<long long> points;
	
	for (int i = 0; i < input.size(); i++) {
		auto it = points.lower_bound(input[i].x);
		if (it != points.end()) {
			check[i] = true;
		}
		else {
			points.insert(input[i].x);
			X.push_back(input[i].x);
			X.push_back(input[i].y);
		}
	}
	X.push_back(2 * l);

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());
	for (int i = 0; i < input.size(); i++) {
		if (check[i] == true)
			continue;
		input[i].x = std::lower_bound(X.begin(), X.end(), input[i].x) - X.begin();
		input[i].y = std::lower_bound(X.begin(), X.end(), input[i].y) - X.begin();
	}

	
	segment_tree min_tree(X.size() + 1, compar1, INT_MAX / 2), max_tree(X.size() + 1, compar2, -1);

	for (int i = 0; i < input.size(); i++) {
		if (check[i] == true)
			continue;
		min_tree.update(1, 0, X.size(), input[i].x, input[i].y, input[i].y);
	}

	for (int i = 0; i < input.size(); i++) {
		if (check[i] == true)
			continue;
		max_tree.update(1, 0, X.size(), input[i].x, input[i].y, input[i].y + 1);
	}

	for (int i = 0; i < X.size(); i++) {
		next[i] = max_tree.query(1, 0, X.size(), i, i);
		if (next[i] == -1)
			next[i] = X.size() - 1;
		else {
			next[i] = min_tree.query(1, 0, X.size(), next[i], next[i]);
			if (next[i] == INT_MAX / 2)
				next[i] = X.size() - 1;
		}
	}
	next[X.size() - 1] = X.size() - 1;

	for (int i = 0; i <= 20; i++) {
		for (int j = 0; j < X.size(); j++) {
			if (i == 0)
				sparse[j][i] = next[j];
			else
				sparse[j][i] = sparse[sparse[j][i - 1]][i - 1];
		}
	}


	int result = INT_MAX / 2;
	for (int i = 0; i < X.size() && X[i] <= l; i++) {
		int cnt = 0, cur = i, ttmp = (1 << 21);
		for (int j = 20; j >= 0; j--) {
			ttmp /= 2;
			if (X[sparse[cur][j]] >= X[i] + l)
				continue;
			cur = sparse[cur][j];
			cnt += ttmp;
		}
		cnt++;
		result = std::min(result, cnt);
	}
	printf("%d\n", result);
}