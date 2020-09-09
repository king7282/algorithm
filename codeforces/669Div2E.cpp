#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>
#include <queue>

struct node {
	int next, color;
	node(int next, int color) : next(next), color(color) {}
};

struct info {
	int cur, color, weight;
	info(int cur, int color, int weight) : cur(cur), color(color), weight(weight) {}
};

bool operator<(info a, info b) {
	return a.weight > b.weight;
}

std::priority_queue<info> qu;
std::vector<node> reverse[500010];
int weights[500010][2];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if(a != b)
			reverse[b].push_back(node(a, c));
	}

	for (int i = 1; i <= n; i++) {
		weights[i][0] = weights[i][1] = INT_MAX / 2;
	}
	
	weights[n][0] = weights[n][1] = 0;
	qu.push(info(n, 0, 0));
	qu.push(info(n, 1, 0));

	while (!qu.empty()) {
		info front = qu.top();
		qu.pop();

		if (front.weight > weights[front.cur][front.color])
			continue;

		for (int i = 0; i < reverse[front.cur].size(); i++) {
			int next = reverse[front.cur][i].next, color = reverse[front.cur][i].color;
			if (weights[next][color] > front.weight + 1) {
				weights[next][color] = front.weight + 1;
				if (weights[next][(color + 1) % 2] != INT_MAX / 2) {
					if (weights[next][color] > weights[next][(color + 1) % 2]) {
						qu.push(info(next, color, weights[next][color]));
					}
					else {
						qu.push(info(next, (color + 1) % 2, weights[next][color]));
					}
				}
			}
		}
	}

	int value = std::max(weights[1][0], weights[1][1]);

	if (value == INT_MAX / 2)
		value = -1;

	printf("%d\n", value);
	for (int i = 1; i <= n; i++) {
		if (weights[i][0] < weights[i][1])
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}