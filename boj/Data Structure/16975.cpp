#include <stdio.h>
#include <algorithm>
#define SIZE 131072

long long tree[SIZE * 2 + 1];

void update(int num, long long val) {
	num |= SIZE;

	tree[num] += val;
	while (num >>= 1)
		tree[num] = tree[num << 1] + tree[num << 1 | 1];
}

long long query(int s, int e) {
	s |= SIZE, e |= SIZE;
	long long r = 0;

	while (s <= e) {
		if (s % 2 == 1) r += tree[s];
		if (e % 2 == 0) r += tree[e];

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);

	int prev = 0;
	for (int i = 1; i <= n; i++) {
		long long a;
		scanf("%lld", &a);

		update(i, a - prev);
		prev = a;
	}

	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int type;
		scanf("%d", &type);

		if (type == 1) {
			int a, b;
			long long c;
			scanf("%d %d %lld", &a, &b, &c);

			update(a, c);
			update(b + 1, -1 * c);
		}
		else {
			int x;
			scanf("%d", &x);
			printf("%lld\n", query(0, x));
		}
	}
}