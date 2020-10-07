#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>

struct info {
	int next;
	long long weight;
	info(int next, long long weight) : next(next), weight(weight) {}
};

bool operator<(info a, info b) {
	return a.weight > b.weight;
}

long long dp[5010][2], C[5010][5010], sum[5010][5010];
long long visits[5010], r_visits[5010];
std::vector<info> graph[5010], reverse[5010];
std::vector<int> X;

void func(int num, int s, int e, int p, int q) {
	if (s > e)
		return;

	int mid = (s + e) / 2, index = -1;
	dp[mid][num % 2] = LLONG_MAX / 2;

	for (int i = p; i <= std::min(q, mid); i++) {
		long long tmp = dp[i - 1][(num - 1) % 2] + C[i][mid];
		if (tmp < dp[mid][num % 2]) {
			dp[mid][num % 2] = tmp;
			index = i;
		}
	}

	func(num, s, mid - 1, p, index);
	func(num, mid + 1, e, index, q);
}

int main(void) {
	int n, b, s, r;
	scanf("%d %d %d %d", &n, &b, &s, &r);

	for (int i = 1; i <= r; i++) {
		int a, z;
		long long c;
		scanf("%d %d %lld", &a, &z, &c);

		graph[a].push_back(info(z, c));
		reverse[z].push_back(info(a, c));
	}

	memset(visits, 0x7f, sizeof(visits));
	std::priority_queue<info> qu;
	visits[b + 1] = 0;
	qu.push(info(b + 1, 0));

	while (!qu.empty()) {
		info top = qu.top();
		qu.pop();

		for (int i = 0; i < graph[top.next].size(); i++) {
			if (visits[graph[top.next][i].next] > top.weight + graph[top.next][i].weight) {
				visits[graph[top.next][i].next] = top.weight + graph[top.next][i].weight;
				qu.push(info(graph[top.next][i].next, top.weight + graph[top.next][i].weight));
			}
		}
	}

	memset(r_visits, 0x7f, sizeof(visits));
	r_visits[b + 1] = 0;
	qu.push(info(b + 1, 0));
	while (!qu.empty()) {
		info top = qu.top();
		qu.pop();

		for (int i = 0; i < reverse[top.next].size(); i++) {
			if (r_visits[reverse[top.next][i].next] > top.weight + reverse[top.next][i].weight) {
				r_visits[reverse[top.next][i].next] = top.weight + reverse[top.next][i].weight;
				qu.push(info(reverse[top.next][i].next, top.weight + reverse[top.next][i].weight));
			}
		}
	}

	for (int i = 1; i <= b; i++)
		X.push_back(i);

	std::sort(X.begin(), X.end(), [&](int a, int b) {
		return r_visits[a] + visits[a] > r_visits[b] + visits[b];
	});


	for (int i = 1; i <= X.size(); i++) {
		for (int j = i + 1; j <= X.size(); j++) {
			sum[i][j] = sum[i][j - 1] + (visits[X[i - 1]] + r_visits[X[j - 1]] + visits[X[j - 1]] + r_visits[X[i - 1]]);
		}
	}

	for (int i = X.size(); i >= 1; i--) {
		for (int j = i - 1; j >= 1; j--) {
			C[j][i] = C[j + 1][i] + sum[j][i];
		}
	}

	for (int i = 1; i <= b; i++)
		dp[i][0] = LLONG_MAX / 2;

	for (int i = 1; i <= s; i++) {
		func(i, i + 1, b, i, b);
		dp[i][i % 2] = 0;
	}

	printf("%lld\n", dp[b][s % 2]);
}