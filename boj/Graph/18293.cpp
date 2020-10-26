#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

struct info {
	int next, type;
	info(int next, int type) : next(next), type(type) {}
};

struct node {
	int next, dist, weight;
	node(int next, int dist, int weight) : next(next), dist(dist), weight(weight) {}
};

bool operator<(node a, node b) {
	return a.weight > b.weight;
}

std::priority_queue<node> qu;
int check[1010][110];
std::vector<info> graph[1010];
int c_cost[110];
std::pair<int, int> station[1010];

int func(int a, int b) {
	int num = (station[a].first - station[b].first) * (station[a].first - station[b].first) + (station[a].second - station[b].second) * (station[a].second - station[b].second);

	int s = 0, e = 200, r = 200;
	while (s <= e) {
		int mid = (s + e) / 2;
		if (mid * mid >= num) {
			r = std::min(r, mid);
			e = mid - 1;
		}
		else
			s = mid + 1;
	}

	return r;
}

int main(void) {
	int sx, sy, fx, fy, d;

	scanf("%d %d %d %d", &sx, &sy, &fx, &fy);
	scanf("%d", &d);

	scanf("%d", &c_cost[0]);
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", c_cost + i);

	int t;
	scanf("%d", &t);

	station[0].first = sx, station[0].second = sy;
	station[t + 1].first = fx, station[t + 1].second = fy;
	graph[0].push_back(info(t + 1, 0));
	
	for (int i = 1; i <= t; i++) {
		graph[0].push_back(info(i, 0));
		graph[i].push_back(info(t + 1, 0));

		scanf("%d %d", &station[i].first, &station[i].second);
		int k;
		scanf("%d", &k);

		for (int j = 1; j <= k; j++) {
			int a, b;
			scanf("%d %d", &a, &b);
			a++;
			graph[i].push_back(info(a, b));
			graph[a].push_back(info(i, b));
		}
	}

	memset(check, 0x7f, sizeof(check));
	check[0][0] = 0;
	qu.push(node(0, 0, 0));

	while (!qu.empty()) {
		node top = qu.top();
		qu.pop();

		for (int i = 0; i < graph[top.next].size(); i++) {
			int dist = func(top.next, graph[top.next][i].next);
			if (top.dist + dist > d)
				continue;

			if (check[graph[top.next][i].next][top.dist + dist] > top.weight + dist * c_cost[graph[top.next][i].type]) {
				check[graph[top.next][i].next][top.dist + dist] = top.weight + dist * c_cost[graph[top.next][i].type];
				qu.push(node(graph[top.next][i].next, top.dist + dist, top.weight + dist * c_cost[graph[top.next][i].type]));
			}
		}
	}

	int result = INT_MAX / 2;
	for (int i = 0; i <= d; i++) {
		result = std::min(result, check[t + 1][i]);
	}

	if (result == INT_MAX / 2)
		printf("-1\n");
	else
		printf("%d\n", result);
}