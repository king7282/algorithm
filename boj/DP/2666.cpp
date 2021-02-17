#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <queue>
#include <climits>


struct node {
	int num, bitmask;
	node(int num, int bitmask) : num(num), bitmask(bitmask) {}
};

int visited[20][(1 << 20) + 1], n, k, seq[20];

int main(void) {
	int start = 0;
	scanf("%d", &n);

	int a, b;
	scanf("%d %d", &a, &b);
	a--;
	b--;

	for (int i = 0; i < n; i++) {
		if (i != a && i != b)
			start |= (1 << i);
	}

	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d", seq + i);
		seq[i]--;
	}

	if (k == 0) {
		printf("0\n");
		return 0;
	}

	memset(visited, -1, sizeof(visited));
	std::deque<node> qu;
	visited[0][start] = 0;
	qu.push_back(node(0, start));
	int result = INT_MAX / 2;

	while (!qu.empty()) {
		node front = qu.front();
		qu.pop_front();

		if ((front.bitmask & (1 << seq[front.num])) == 0) {
			if (front.num == k - 1) {
				result = std::min(result, visited[front.num][front.bitmask]);
			}
			else {
				visited[front.num + 1][front.bitmask] = visited[front.num][front.bitmask];
				qu.push_front(node(front.num + 1, front.bitmask));
			}
		}

		for (int i = 0; i < n; i++) {
			if ((front.bitmask & (1 << i)) != 0)
				continue;

			int next_bitmask;

			if (i != 0 && (front.bitmask & (1 << (i - 1))) != 0) {
				next_bitmask = ((front.bitmask | (1 << i)) ^ (1 << (i - 1)));
				if (visited[front.num][next_bitmask] == -1) {
					visited[front.num][next_bitmask] = visited[front.num][front.bitmask] + 1;
					qu.push_back(node(front.num, next_bitmask));
				}
			}

			if (i != n - 1 && (front.bitmask & (1 << (i + 1))) != 0) {
				next_bitmask = ((front.bitmask | (1 << i)) ^ (1 << (i + 1)));
				if (visited[front.num][next_bitmask] == -1) {
					visited[front.num][next_bitmask] = visited[front.num][front.bitmask] + 1;
					qu.push_back(node(front.num, next_bitmask));
				}
			}

		}
	}

	printf("%d\n", result);
}