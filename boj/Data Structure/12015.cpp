#include <stdio.h>
#include <algorithm>
#define SIZE 1048576

int tree[SIZE * 2 + 1];

void update(int num, int val) {
	num |= SIZE;
	tree[num] = std::max(tree[num], val);

	while (num >>= 1)
		tree[num] = std::max(tree[num << 1], tree[num << 1 | 1]);
}

int query(int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = 0;

	while (s <= e) {
		if (s % 2 == 1) r = std::max(r, tree[s]);
		if (e % 2 == 0) r = std::max(r, tree[e]);

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int input;
		scanf("%d", &input);

		update(input, query(0, input - 1) + 1);
	}

	printf("%d\n", query(1, 1000000));
}