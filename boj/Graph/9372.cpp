#include <stdio.h>
#include <algorithm>
#include <cstring>

int tree[1010];

int find(int num) {
	if (tree[num] == -1)
		return num;
	return tree[num] = find(tree[num]);
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n, m;
		scanf("%d %d", &n, &m);

		memset(tree, -1, sizeof(tree));
		int result = 0;

		for (int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);

			a = find(a), b = find(b);

			if (a != b) {
				result++;
				tree[a] = b;
			}
		}

		printf("%d\n", result);
	}
}