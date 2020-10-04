#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#define SIZE 131072

struct info {
	int num, index;
	long long weight;
	info(int num, int index, long long weight) : num(num), index(index), weight(weight) {}
};

struct node {
	int next;
	long long weight;
	node(int next, long long weight) : next(next), weight(weight) {}
};

bool operator<(info a, info b) {
	return a.weight > b.weight;
}

std::priority_queue<info> qu;
std::vector<node> graph[SIZE];
int cnt[SIZE];
long long visits[SIZE][2]; // 0 is left, 1 is right

int main(void) {
	int n, m, s, t;
	scanf("%d %d %d %d", &n, &m, &s, &t);

	for (int i = 1; i <= m; i++) {
		int a, b;
		long long c;
		scanf("%d %d %lld", &a, &b, &c);
		graph[b].push_back(node(a, c));
		cnt[a]++;
	}

	for (int i = 0; i < n; i++) {
		visits[i][0] = -1;
		visits[i][1] = LLONG_MAX / 2;
	}

	visits[t][0] = 0;
	visits[t][1] = 0;
	qu.push(info(t, 0, 0));
	qu.push(info(t, 1, 0));

	while (!qu.empty()) {
		info cur = qu.top();
		qu.pop();

		if (visits[cur.num][cur.index] != cur.weight)
			continue;

		for (int i = 0; i < graph[cur.num].size(); i++) {
			int next = graph[cur.num][i].next;
			long long weight = graph[cur.num][i].weight;

			if (cur.index == 0) {
				if (visits[next][1] > visits[cur.num][0] + weight) {
					visits[next][1] = visits[cur.num][0] + weight;
					qu.push(info(next, 1, visits[next][1]));
				}
			}
			else {
				if (visits[next][0] < visits[cur.num][1] + weight) {
					visits[next][0] = visits[cur.num][1] + weight;
				}
				cnt[next]--;
				if (cnt[next] == 0) {
					qu.push(info(next, 0, visits[next][0]));
				}
			}
		}
	}

	if (visits[s][0] == -1 || cnt[s] > 0)
		printf("infinity\n");
	else
		printf("%lld\n", visits[s][0]);
}