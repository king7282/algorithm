#include <stdio.h>
#include <algorithm>
#include <climits>
#define SIZE 131072

std::pair<int, int> tree[SIZE * 2 + 1];

void update(int num, std::pair<int, int> val) {
	num |= SIZE;
	tree[num] = val;

	while (num >>= 1)
		tree[num] = std::min(tree[num << 1], tree[num << 1 | 1]);
}

std::pair<int, int> query(int s, int e) {
	s |= SIZE, e |= SIZE;
	std::pair<int, int> r = std::make_pair(INT_MAX / 2, INT_MAX / 2);
	
	while (s <= e) {
		if (s % 2 == 1) r = std::min(r, tree[s]);
		if (e % 2 == 0) r = std::min(r, tree[e]);

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		update(i, std::make_pair(a, i));
	}

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int a, b;
			scanf("%d %d", &a, &b);
			update(a, std::make_pair(b, a));
		}
		else {
            int a, b;
            scanf("%d %d", &a, &b);
			printf("%d\n", query(a, b).second);
		}
	}

}