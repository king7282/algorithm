#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <climits>
#define SIZE 2097152

struct point {
	long long x, y;
	point(long long x, long long y) : x(x), y(y) {}
};

bool map[32][210][210];
int mov[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1} };
std::pair<int, int> lazy[SIZE * 2 + 1], tree[SIZE * 2 + 1];

void init(int node, int start, int end) {
	lazy[node] = std::make_pair(INT_MAX / 2, INT_MIN / 2);
	if (start == end)
		tree[node] = std::make_pair(INT_MAX / 2, INT_MIN / 2);
	else {
		init(node << 1, start, (start + end) >> 1);
		init((node << 1) | 1, ((start + end) >> 1) + 1, end);
		tree[node] = std::make_pair(INT_MAX / 2, INT_MIN / 2);
	}
}

void lazy_propagation(int node, int start, int end) {
	if (lazy[node] != std::make_pair(INT_MAX / 2, INT_MIN / 2)) {
		tree[node].first = std::min(tree[node].first, lazy[node].first);
		tree[node].second = std::max(tree[node].second, lazy[node].second);
		if (start != end) {
			lazy[node << 1].first = std::min(lazy[node << 1].first, lazy[node].first);
			lazy[node << 1].second = std::max(lazy[node << 1].second, lazy[node].second);

			lazy[node << 1 | 1].first = std::min(lazy[node << 1 | 1].first, lazy[node].first);
			lazy[node << 1 | 1].second = std::max(lazy[node << 1 | 1].second, lazy[node].second);
		}
		lazy[node] = std::make_pair(INT_MAX / 2, INT_MIN / 2);
	}
}

void update(int node, int start, int end, int i, int j, std::pair<int, int> val) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return;
	if (i <= start && end <= j) {
		tree[node].first = std::min(tree[node].first, val.first);
		tree[node].second = std::max(tree[node].second, val.second);
		if (start != end) {
			lazy[node << 1].first = std::min(lazy[node << 1].first, val.first);
			lazy[node << 1].second = std::max(lazy[node << 1].second, val.second);
			lazy[node << 1 | 1].first = std::min(lazy[node << 1 | 1].first, val.first);
			lazy[node << 1 | 1].second = std::max(lazy[node << 1 | 1].second, val.second);
		}
		return;
	}
	else {
		update(node << 1, start, (start + end) / 2, i, j, val);
		update((node << 1) | 1, (start + end) / 2 + 1, end, i, j, val);
		tree[node].first = std::min(tree[node << 1].first, tree[node << 1 | 1].first);
		tree[node].second = std::max(tree[node << 1].second, tree[node << 1 | 1].second);
	}
}

std::pair<int, int> query(int node, int start, int end, int i, int j) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return std::make_pair(INT_MAX / 2, INT_MIN / 2);
	if (i <= start && end <= j)
		return tree[node];

	std::pair<int, int> left = query(node * 2, start, (start + end) / 2, i, j), right = query(node * 2 + 1, (start + end) / 2 + 1, end, i, j);
	return std::make_pair(std::min(left.first, right.first), std::max(left.second, right.second));
}

int main(void) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	getchar();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c;
			scanf("%c", &c);
			if (c == '#')
				map[1][i + 100][j + 100] = true;
		}

		getchar();
	}

	for (int i = 1; i <= std::min(30, k); i++) {
		int cur = i, next = i + 1;

		for (int j = 1; j <= 200; j++) {
			for (int t = 1; t <= 200; t++) {
				if (map[cur][j][t] == true) {
					map[next][j][t] = true;
					for (int a = 0; a < 8; a++) {
						int nx = j + mov[a][0], ny = t + mov[a][1];
						map[next][nx][ny] = true;
					}
				}
			}
		}
	}

	if (k <= 30) {
		int result = 0;
		for (int i = 1; i <= 200; i++) {
			for (int j = 1; j <= 200; j++) {
				if (map[k + 1][i][j] == true)
					result++;
			}
		}
		printf("%d\n", result);
	}
	else {
		k -= 30;
		int minx = INT_MAX / 2, maxx = INT_MIN / 2;
		std::vector<int> X;
		for (int i = 1; i <= 200; i++) {
			for (int j = 1; j <= 200; j++) {
				if (map[31][i][j] == true) {
					minx = std::min(minx, i - k);
					maxx = std::max(maxx, i + k);
				}
			}
		}

		for (int i = minx; i <= maxx; i++)
			X.push_back(i);

		init(1, 0, X.size());
		for (int i = 1; i <= 200; i++) {
			for (int j = 1; j <= 200; j++) {
				if (map[31][i][j] == true) {
					int lower = std::lower_bound(X.begin(), X.end(), i - k) - X.begin();
					int upper = std::lower_bound(X.begin(), X.end(), i + k) - X.begin();

					update(1, 0, X.size(), lower, upper, std::make_pair(j - k, j + k));
				}
			}
		}

		long long result = 0, prev = 0;
		for (int i = 0; i < X.size(); i++) {
			std::pair<int, int> qu = query(1, 0, X.size(), i, i);
			result += qu.second - qu.first + 1;
		}

		printf("%lld\n", result);
	}
}