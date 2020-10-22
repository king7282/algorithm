#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#define SIZE 2097152

struct info {
	int x, y;
	info(int x, int y) : x(x), y(y) {}
};

std::vector<info> lines;
int lazy[SIZE * 2 + 1], tree[SIZE * 2 + 1], next[SIZE];
int sparse[SIZE][25];
int n, k;

void init(int node, int start, int end) {
	lazy[node] = 0;
	if (start == end)
		tree[node] = 0;
	else {
		init(node << 1, start, (start + end) >> 1);
		init((node << 1) | 1, ((start + end) >> 1) + 1, end);
		tree[node] = std::max(tree[node * 2], tree[node * 2 + 1]);
	}
}

void lazy_propagation(int node, int start, int end) {
	if (lazy[node] != 0) {
		tree[node] = std::max(tree[node], lazy[node]);
		if (start != end) {
			lazy[node << 1] = std::max(lazy[node << 1], lazy[node]);
			lazy[(node << 1) | 1] = std::max(lazy[node << 1 | 1], lazy[node]);
		}
		lazy[node] = 0;
	}
}

void update(int node, int start, int end, int i, int j, int val) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return;
	if (i <= start && end <= j) {
		tree[node] = std::max(tree[node], val);
		if (start != end) {
			lazy[node << 1] = std::max(lazy[node << 1], val);
			lazy[(node << 1) | 1] = std::max(lazy[(node << 1) | 1], val);
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

bool OK(int num, int cur) {
	int start = cur, ttmp = num;
	while (num > 0) {
		int j = 0, tmp = 1;
		while (tmp <= num) {
			tmp *= 2;
			j++;
		}

		cur = sparse[cur][j - 1];
		num -= tmp / 2;
	}
	return cur >= start + n;
}

int main(void) {
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= k; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a > b) {
			a -= n;
		}

		lines.push_back(info(a, b));
		lines.push_back(info(a + n, b + n));
		lines.push_back(info(a + 2 * n, b + 2 * n));
	}

	std::sort(lines.begin(), lines.end(), [](info a, info b) {
		return a.y < b.y;
	});

	init(1, 1, 2 * n + 1);

	for (int i = 0; i < lines.size(); i++) {
		if(lines[i].x <= 2 * n)
			update(1, 1, 2 * n + 1, std::max(1, lines[i].x), std::min(lines[i].y, 2 * n), std::min(lines[i].y + 1, 2 * n + 1));
	}
	
	bool flag = true;
	for (int i = 1; i <= 2 * n && flag; i++) {
		next[i] = query(1, 1, 2 * n + 1, i, i);
		if (next[i] == 0)
			flag = false;
	}
	
	if (!flag) {
		printf("impossible\n");
		return 0;
	}

	next[2 * n + 1] = 2 * n + 1;
	for (int i = 0; i <= 24; i++) {
		for (int j = 1; j <= 2 * n + 1; j++) {
			if (i == 0) {
				sparse[j][i] = next[j];
			}
			else {
				sparse[j][i] = sparse[sparse[j][i - 1]][i - 1];
			}
		}
	}
	
	int result = k;
	for (int i = 1; i <= n; i++) {
		int s = 1, e = k, r = k;

		while (s <= e) {
			int mid = (s + e) / 2;
			if (OK(mid, i)) {
				e = mid - 1;
				r = std::min(r, mid);
			}
			else
				s = mid + 1;
		}

		result = std::min(result, r);
	}

	printf("%d\n", result);
}