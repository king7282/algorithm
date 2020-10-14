#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#include <queue>

struct info {
	int val, num, bitmask;
};

int need_mask[20];
long long weights[19], dp[19][19][1 << 18], degree[19], result[19];
std::vector<int> graph[19], order, reverse[19];
bool check[19][19][1 << 18];

long long func(int val, int num, int bitmask) {
	if (bitmask == ((1 << order.size()) - 1)) {
		return 0;
	}

	if (val < 0) {
		return LLONG_MAX / 2;
	}

	if (check[val][num][bitmask] == true)
		return dp[val][num][bitmask];

	check[val][num][bitmask] = true;
	dp[val][num][bitmask] = LLONG_MAX / 2;

	dp[val][num][bitmask] = std::min(dp[val][num][bitmask], func(val - 1, order.size() - 1, bitmask));
	if ((bitmask & (1 << (order[num] - 1))) == 0 && (need_mask[order[num]] | bitmask) == bitmask)
		dp[val][num][bitmask] = std::min(dp[val][num][bitmask], func(val - 1, order.size() - 1, bitmask | (1 << (order[num] - 1))) + weights[order[num]] * val);

	if (num != 0) {
		int next = num - 1;
		if ((bitmask & (1 << (order[num] - 1))) == 0 && (need_mask[order[num]] | bitmask) == bitmask)
			dp[val][num][bitmask] = std::min(dp[val][num][bitmask], func(val, next, bitmask | (1 << (order[num] - 1))) + weights[order[num]] * val);
		dp[val][num][bitmask] = std::min(dp[val][num][bitmask], func(val, next, bitmask));
	}

	return dp[val][num][bitmask];
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		reverse[b].push_back(a);
		graph[a].push_back(b);
		weights[a] += c;
		weights[b] -= c;
		degree[b]++;
	}

	if (m == 0) {
		for (int i = 1; i <= n; i++)
			printf("1 ");
		printf("\n");
		return 0;

	}
	std::queue<int> qu;
	for (int i = 1; i <= n; i++) {
		if (degree[i] == 0) {
			qu.push(i);
		}
	}

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();
		order.push_back(front);

		for (int i = 0; i < graph[front].size(); i++) {
			degree[graph[front][i]]--;
			if (degree[graph[front][i]] == 0) {
				qu.push(graph[front][i]);
			}
		}
	}

	for (int i = 0; i < order.size(); i++) {
		for (int j = 0; j < reverse[order[i]].size(); j++) {
			need_mask[order[i]] |= (need_mask[reverse[order[i]][j]] | (1 << (reverse[order[i]][j] - 1)));
		}
	}

	func(n, order.size() - 1, 0);

	info cur;
	cur.val = n; cur.num = order.size() - 1; cur.bitmask = 0;

	while (cur.bitmask != (1 << n) - 1) {
		info next;

		int nnext = cur.num - 1;

		if (cur.val == 0) {
			if((cur.bitmask | (1 << (order[cur.num] - 1))) == (1 << (n - 1))) {
				next.val = cur.val - 1;
				next.num = order.size() - 1;
				next.bitmask = (cur.bitmask | (1 << (order[cur.num] - 1)));
			}
		}
		else {
			if (dp[cur.val][cur.num][cur.bitmask] == dp[cur.val - 1][order.size() - 1][cur.bitmask]) {
				next.val = cur.val - 1;
				next.num = order.size() - 1;
				next.bitmask = cur.bitmask;
			}

			if ((cur.bitmask & (1 << (order[cur.num] - 1))) == 0 && (need_mask[order[cur.num]] | cur.bitmask) == cur.bitmask) {
				if (dp[cur.val][cur.num][cur.bitmask] == dp[cur.val - 1][order.size() - 1][cur.bitmask | (1 << (order[cur.num] - 1))] + weights[order[cur.num]] * cur.val) {
					next.val = cur.val - 1;
					next.num = order.size() - 1;
					next.bitmask = (cur.bitmask | (1 << (order[cur.num] - 1)));
				}
			}
		}

		if (nnext != -1) {
			if ((cur.bitmask & (1 << (order[cur.num] - 1))) == 0 && (need_mask[order[cur.num]] | cur.bitmask) == cur.bitmask) {
				if (dp[cur.val][cur.num][cur.bitmask] == dp[cur.val][nnext][cur.bitmask | (1 << (order[cur.num] - 1))] + weights[order[cur.num]] * cur.val) {
					next.val = cur.val;
					next.num = nnext;
					next.bitmask = (cur.bitmask | (1 << (order[cur.num] - 1)));
				}
			}
			if (dp[cur.val][cur.num][cur.bitmask] == dp[cur.val][nnext][cur.bitmask]) {
				next.val = cur.val;
				next.num = nnext;
				next.bitmask = cur.bitmask;
			}
		}

		if (cur.bitmask != next.bitmask) {
			for (int i = 1; i <= n; i++) {
				if ((cur.bitmask & (1 << (i - 1))) == 0 && (next.bitmask & (1 << (i - 1))) != 0) {
					result[i] = cur.val;
				}
			}
		}
		cur = next;
	}

	for (int i = 1; i <= n; i++)
		printf("%d ", result[i]);
}