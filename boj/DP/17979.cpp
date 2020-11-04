#include <stdio.h>
#include <algorithm>
#include <climits>
#define SIZE 131072

struct info {
	int x, y, type;
};

int price[110];
info input[10010];
int tree[SIZE * 2 + 1];

void update(int num, int val) {
	num |= SIZE;
	tree[num] = val;

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
	int m, n;
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= m; i++)
		scanf("%d", price + i);

	for (int i = 1; i <= n; i++)
		scanf("%d %d %d", &input[i].x, &input[i].y, &input[i].type);

	std::sort(input + 1, input + 1 + n, [](info a, info b) {
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	});
	input[n + 1].x = input[n + 1].y = INT_MAX / 2;

	for (int i = n; i >= 1; i--) {
		int s = i + 1, e = n + 1, r = n + 1;

		while (s <= e) {
			int mid = (s + e) / 2;
			if (input[mid].x >= input[i].y) {
				r = std::min(r, mid);
				e = mid - 1;
			}
			else
				s = mid + 1;
		}

		update(i, query(r, n) + (input[i].y - input[i].x) * price[input[i].type]);
	}

	printf("%d\n", query(1, n));
}