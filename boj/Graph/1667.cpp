#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>
#include <cassert>

struct info {
	int next;
	long long weight;
	info(int next, long long weight) : next(next), weight(weight) {}
};

bool operator<(info a, info b) {
	return a.weight > b.weight;
}

long long lazy[262144 * 2 + 1], tree[262144 * 2 + 1];
std::pair<long long, long long> line[50010];
std::vector<info> graph[100010];
std::priority_queue<info> qu;
long long visited[100010];

long long aabs(long long num) {
	if (num < 0)
		return num * -1;
	return num;
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

void update(int node, int start, int end, int i, int j, long long val) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return;
	if (i <= start && end <= j) {
		tree[node] = std::max(tree[node], val);
		if (start != end) {
			lazy[node << 1] = std::max(lazy[node << 1], val);
			lazy[(node << 1) | 1] = std::max(lazy[node << 1 | 1], val);
		}
		return;
	}
	else {
		update(node << 1, start, (start + end) / 2, i, j, val);
		update((node << 1) | 1, (start + end) / 2 + 1, end, i, j, val);
		tree[node] = std::max(tree[node << 1], tree[(node << 1) | 1]);
	}
}

long long query(int node, int start, int end, int i, int j) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return 0;
	if (i <= start && end <= j)
		return tree[node];
	return std::max(query(node * 2, start, (start + end) / 2, i, j), query(node * 2 + 1, (start + end) / 2 + 1, end, i, j));
}

int main(void) {
	memset(tree, 0, sizeof(tree));
	memset(lazy, 0, sizeof(lazy));

	int n;
	long long s;
	scanf("%d %lld", &n, &s);
	assert(1 <= n && n <= 50000);
	assert(-100000 <= s && s <= 100000);

	for (int i = n; i >= 1; i--) {
		scanf("%lld %lld", &line[i].first, &line[i].second);
	}

	for (int i = 1; i <= n; i++) {
		assert(-100000 <= line[i].first && line[i].first <= 100000);
		assert(-100000 <= line[i].second && line[i].second <= 100000);
		assert(line[i].first < line[i].second);

		int next = query(1, 0, 200000, line[i].first + 100000, line[i].first + 100000);
		graph[i * 2].push_back(info(next * 2, aabs(line[next].first - line[i].first)));
		graph[i * 2].push_back(info(next * 2 + 1, aabs(line[next].second - line[i].first)));
		next = query(1, 0, 200000, line[i].second + 100000, line[i].second + 100000);
		graph[i * 2 + 1].push_back(info(next * 2, aabs(line[next].first - line[i].second)));
		graph[i * 2 + 1].push_back(info(next * 2 + 1, aabs(line[next].second - line[i].second)));
		update(1, 0, 200000, line[i].first + 100000, line[i].second + 100000, i);
	
	}

	for (int i = 0; i <= 2 * n + 1; i++)
		visited[i] = LLONG_MAX / 2;

	int start = query(1, 0, 200000, s + 100000, s + 100000);
	visited[start * 2] = aabs(s - line[start].first);
	visited[start * 2 + 1] = aabs(s - line[start].second);

	qu.push(info(start * 2, visited[start * 2]));
	qu.push(info(start * 2 + 1, visited[start * 2 + 1]));

	while (!qu.empty()) {
		info top = qu.top();
		qu.pop();
		for (int i = 0; i < graph[top.next].size(); i++) {
			if (visited[graph[top.next][i].next] > graph[top.next][i].weight + top.weight) {
				visited[graph[top.next][i].next] = graph[top.next][i].weight + top.weight;
				qu.push(info(graph[top.next][i].next, visited[graph[top.next][i].next]));
			}
		}
	}


	printf("%lld\n", std::min(visited[0], visited[1]));
}