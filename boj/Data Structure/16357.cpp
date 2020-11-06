#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 262144

struct segment_tree {
	int lazy[SIZE * 2 + 1], tree[SIZE * 2 + 1], a[SIZE];

	void init(int node, int start, int end) {
		lazy[node] = 0;
		if (start == end)
			tree[node] = a[start];
		else {
			init(node << 1, start, (start + end) >> 1);
			init((node << 1) | 1, ((start + end) >> 1) + 1, end);
			tree[node] = std::max(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void lazy_propagation(int node, int start, int end) {
		if (lazy[node] != 0) {
			tree[node] += lazy[node];
			if (start != end) {
				lazy[node << 1] += lazy[node];
				lazy[(node << 1) | 1] += lazy[node];
			}
			lazy[node] = 0;
		}
	}

	void update(int node, int start, int end, int i, int j, int val) {
		lazy_propagation(node, start, end);
		if (i > end || j < start)
			return;
		if (i <= start && end <= j) {
			tree[node] += val;
			if (start != end) {
				lazy[node << 1] += val;
				lazy[(node << 1) | 1] += val;
			}
			return;
		}
		else {
			update(node << 1, start, (start + end) / 2, i, j, val);
			update((node << 1) | 1, (start + end) / 2 + 1, end, i, j, val);
			tree[node] = std::max(tree[node << 1], tree[(node << 1) | 1]);
		}
	}

	int query(int node, int start, int end, int i, int j) {
		lazy_propagation(node, start, end);
		if (i > end || j < start)
			return 0;
		if (i <= start && end <= j)
			return tree[node];
		return std::max(query(node * 2, start, (start + end) / 2, i, j), query(node * 2 + 1, (start + end) / 2 + 1, end, i, j));
	}
};

struct info {
	int l, r;
	info(int l, int r) : l(l), r(r) {}
};

std::pair<int, int> input[100010];
std::vector<info> start[SIZE], end[SIZE];

int main(void) {
	int n;
	scanf("%d", &n);
	std::vector<int> Y;
	segment_tree first, second;
	for (int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d %d %d %d", &a, &input[i].second, &b, &input[i].first);
		Y.push_back(input[i].first);
		Y.push_back(input[i].second);
	}

	std::sort(Y.begin(), Y.end());
	Y.erase(std::unique(Y.begin(), Y.end()), Y.end());
	first.init(1, 0, SIZE - 1);
	second.init(1, 0, SIZE - 1);

	for (int i = 1; i <= n; i++) {
		input[i].first = std::lower_bound(Y.begin(), Y.end(), input[i].first) - Y.begin();
		input[i].second = std::lower_bound(Y.begin(), Y.end(), input[i].second) - Y.begin();

		start[input[i].first].push_back(info(input[i].first, input[i].second));
		end[input[i].second].push_back(info(input[i].first, input[i].second));
		second.update(1, 0, SIZE - 1, input[i].first, input[i].second, 1);
	}

	int result = 0;
	for (int i = 0; i < Y.size(); i++) {
		for (int j = 0; j < start[i].size(); j++) {
			second.update(1, 0, SIZE - 1, start[i][j].l, start[i][j].r, -1);
			first.update(1, 0, SIZE - 1, start[i][j].l, start[i][j].r, 1);
		}

		result = std::max(result, first.query(1, 0, SIZE - 1, i, i) + second.query(1, 0, SIZE - 1, 0, Y.size() - 1));
		for (int j = 0; j < end[i].size(); j++) {
			second.update(1, 0, SIZE - 1, end[i][j].l, end[i][j].r, 1);
			first.update(1, 0, SIZE - 1, end[i][j].l, end[i][j].r, -1);
		}
	}

	printf("%d\n", result);
}