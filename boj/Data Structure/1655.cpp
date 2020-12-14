#include <stdio.h>
#define SIZE 32768

int tree[SIZE * 2 + 1];

void update(int num, int val) {
	num |= SIZE;
	tree[num] += val;
	while (num >>= 1)
		tree[num] = tree[num << 1] + tree[num << 1 | 1];
}

int kth_element(int node, int k) {
	if (node >= SIZE)
		return node - SIZE;

	if (tree[node << 1] >= k) {
		return kth_element(node << 1, k);
	}
	else
		return kth_element(node << 1 | 1, k - tree[node << 1]);
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int input;
		scanf("%d", &input);
		update(input + 10000, 1);

		printf("%d\n", kth_element(1, i / 2 + 1) - 10000);
	}
}