#include <stdio.h>
#include <algorithm>
#define SIZE 1048576

long long tree[SIZE * 2 + 1];

void update(int num, long long val) {
	num |= SIZE;
	tree[num] = val;

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
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++) {
		long long input;
		scanf("%lld", &input);
		update(i, input);
	}


	for (int i = 1; i <= m + k; i++) {
		int type;
		long long s, e;
		scanf("%d %lld %lld", &type, &s, &e);

		if (type == 1) {
			update(s, e);
		}
		else {
			printf("%lld\n", query(s, e));
		}
	}

}