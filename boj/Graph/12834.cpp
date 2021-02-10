#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>

struct node {
	int next, weights;
	node(int next, int weights) : next(next), weights(weights) {}
};

bool operator<(node a, node b) {
	return a.weights > b.weights;
}

std::vector<node> graph[1010];
int starts[110], visited[1010];
int kist, seafood;

int solve(int s) {
	memset(visited, -1, sizeof(visited));
	std::priority_queue<node> qu;

	qu.push(node(s, 0));
	visited[s] = 0;

	while (!qu.empty()) {
		node top = qu.top();
		qu.pop();

		if (visited[top.next] != top.weights)
			continue;

		for (int i = 0; i < graph[top.next].size(); i++) {
			int next = graph[top.next][i].next;

			if (visited[next] == -1 || visited[next] > top.weights + graph[top.next][i].weights) {
				visited[next] = top.weights + graph[top.next][i].weights;
				qu.push(node(next, visited[next]));
			}
		}
	}

	return visited[kist] + visited[seafood];
}

int main(void) {
	int n, v, e;
	scanf("%d %d %d", &n, &v, &e);

	scanf("%d %d", &kist, &seafood);

	for (int i = 1; i <= n; i++)
		scanf("%d", starts + i);

	for (int i = 1; i <= e; i++) {
		int a, b, l;
		scanf("%d %d %d", &a, &b, &l);

		graph[a].push_back(node(b, l));
		graph[b].push_back(node(a, l));
	}

	int result = 0;
	for (int i = 1; i <= n; i++) {
		result += solve(starts[i]);
	}

	printf("%d\n", result);
}