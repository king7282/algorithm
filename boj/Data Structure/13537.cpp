#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 131072

int tree[SIZE * 2 + 1];

void update(int num, int val) {
	num |= SIZE;
	tree[num] += val;

	while (num >>= 1)
		tree[num] = tree[num << 1] + tree[num << 1 | 1];
}

int query(int s, int e) {
	s |= SIZE, e |= SIZE;

	int r = 0;
	while (s <= e) {
		if (s % 2 == 1) r += tree[s];
		if (e % 2 == 0) r += tree[e];

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

struct info {
	int x, y, k, index;
};

std::pair<int, int> input[SIZE];
info qu[SIZE];
int result[SIZE];

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &input[i].first);
		input[i].second = i;

	}
	std::sort(input + 1, input + 1 + n);

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		scanf("%d %d %d", &qu[i].x, &qu[i].y, &qu[i].k);
		qu[i].index = i;
	}

	std::sort(qu + 1, qu + 1 + q, [](info a, info b) {
		return a.k > b.k;
	});

	std::vector<int> upd;
	int prev = qu[1].k, index = n;
	for (int i = 1; i <= q; i++) {
		if (qu[i].k != prev) {
			for (int j = 0; j < upd.size(); j++) {
				result[qu[upd[j]].index] = query(qu[upd[j]].x, qu[upd[j]].y);
			}
			upd.clear();
		}
		while (index >= 1 && input[index].first > qu[i].k) {
			update(input[index].second, 1);
			index--;
		}

		prev = qu[i].k;
		upd.push_back(i);
	}

	for (int i = 0; i < upd.size(); i++) {
		result[qu[upd[i]].index] = query(qu[upd[i]].x, qu[upd[i]].y);
	}

	for (int i = 1; i <= q; i++) {
		printf("%d\n", result[i]);
	}
}