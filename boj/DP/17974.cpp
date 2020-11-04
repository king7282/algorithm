#include <stdio.h>
#include <algorithm>
#include <climits>
#define SIZE 131072

int dist[100010], colors[100010];
int tree[SIZE * 2 + 1];

void update(int num, int val) {
	num |= SIZE;
	tree[num] = val;

	while (num >>= 1)
		tree[num] = std::min(tree[num << 1], tree[num << 1 | 1]);
}

int query(int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = INT_MAX / 2;
	while (s <= e) {
		if (s % 2 == 1) r = std::min(r, tree[s]);
		if (e % 2 == 0) r = std::min(r, tree[e]);

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}

int main(void) {
	int m, n;
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", dist + i);
	for (int i = 1; i <= n; i++)
		scanf("%d", colors + i);

	dist[0] = INT_MIN / 2;
	int ps = 0, pe = 0, tmp = 0;
	for (int i = 1; i <= n; i++) {
		if (colors[i - 1] != colors[i]) {
			ps = tmp;
			pe = i - 1;
			tmp = i;
		}

		int s = ps, e = pe, r1 = pe + 1;
		while (s <= e) {
			int mid = (s + e) / 2;
			if (dist[pe] - dist[mid] <= dist[i] - dist[pe]) {
				e = mid - 1;
				r1 = std::min(r1, mid);
			}
			else
				s = mid + 1;
		}

		s = ps, e = pe;
		int r2 = ps - 1;
		while (s <= e) {
			int mid = (s + e) / 2;
			if (dist[tmp] - dist[mid] >= dist[i] - dist[tmp]) {
				s = mid + 1;
				r2 = std::max(r2, mid);
			}
			else
				e = mid - 1;
		}

		update(i, std::min(query(r1, r2), query(tmp, i - 1)) + 1);
	}

	printf("%d\n", query(tmp, n));
}