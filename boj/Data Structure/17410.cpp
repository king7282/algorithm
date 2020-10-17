#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 16384

int input[100010], next[100010], tree[510][SIZE * 2 + 1], di[100010];
int pq = 1200;

void update(int index, int num, int val) {
	num |= SIZE;

	tree[index][num] += val;
	while (num >>= 1)
		tree[index][num] = tree[index][num << 1] + tree[index][num << 1 | 1];
}

int query(int index, int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = 0;

	while (s <= e) {
		if (s % 2 == 1) r += tree[index][s];
		if (e % 2 == 0) r += tree[index][e];

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

int main(void) {
	int n, max1 = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", input + i);

		next[i] = (i / pq + 1) * pq;
		di[i] = i / pq;
		max1 = std::max(max1, input[i]);
		update(di[i], input[i], 1);
	}

	int q;
	scanf("%d", &q);
	std::vector<int> r1;

	for (int i = 1; i <= q; i++) {
		int a;
		scanf("%d", &a);

		if (a == 1) {
			int b, c;
			scanf("%d %d", &b, &c);
			b--;

			update(di[b], input[b], -1);
			update(di[b], c, 1);
			input[b] = c;
			max1 = std::max(max1, c);
		}
		else {
			int b, c, d;
			scanf("%d %d %d", &b, &c, &d);
			b--;
			c--;

			int result = 0;
			if (di[b] == di[c]) {
				for (int j = b; j <= c; j++) {
					if (input[j] > d)
						result++;
				}
			}
			else {
				int start = di[b] + 1, end = di[c] - 1;

				for (int j = b; j < next[b]; j++) {
					if (input[j] > d)
						result++;
				}

				for (int j = start; j <= end; j++) {
					result += query(j, d + 1, max1);
				}

				for (int j = di[c] * pq; j <= c; j++) {
					if (input[j] > d)
						result++;
				}
			}
			r1.push_back(result);
		}
	}

	for (int i = 0; i < r1.size(); i++)
		printf("%d\n", r1[i]);
}