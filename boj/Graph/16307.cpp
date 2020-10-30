#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>

struct info {
	int l, r, v;
};

struct node {
	int a, b, value;
	node(int a, int b, int value) : a(a), b(b), value(value) {}
};

int tree[100010];
info input[100010];

int find(int num) {
	if (tree[num] == -1)
		return num;
	return tree[num] = find(tree[num]);
}

int main(void) {
	int n, a, b;
	scanf("%d %d %d", &n, &a, &b);

	for (int i = 0; i < n; i++)
		scanf("%d %d %d", &input[i].l, &input[i].r, &input[i].v);

	memset(tree, -1, sizeof(tree));
	std::queue<node> qu;
	qu.push(node(a, b, 0));
	int result = INT_MAX / 2;

	while (!qu.empty()) {
		node front = qu.front();
		qu.pop();

		if (input[front.a].v != input[front.b].v) {
			result = std::min(result, front.value);
		}

		if (find(front.a) == find(front.b))
			continue;
		tree[find(front.a)] = find(front.b);
		qu.push(node(input[front.a].l, input[front.b].l, front.value + 1));
		qu.push(node(input[front.a].r, input[front.b].r, front.value + 1));
	}

	if (result == INT_MAX / 2)
		printf("indistinguishable\n");
	else
		printf("%d\n", result);
}