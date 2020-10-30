#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 131072

struct info {
	int type, x, y, k;
};

info qu[100010];
int input[100010], pq = 1000;
int tree[110][SIZE * 2 + 1];
std::vector<int> X;

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
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", input + i);
	}

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		scanf("%d", &qu[i].type);

		if (qu[i].type == 1) {
			scanf("%d %d %d", &qu[i].x, &qu[i].y, &qu[i].k);
			qu[i].x--;
			qu[i].y--;
			X.push_back(qu[i].k);
		}
		else {
			scanf("%d %d", &qu[i].x, &qu[i].k);
			qu[i].x--;
		}
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	for (int i = 0; i < n; i++) {
		int index = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
		index--;
		if (index != -1)
			update(i / pq, index, 1);
	}

	for (int i = 1; i <= q; i++) {
		if (qu[i].type == 1) {
			int start = qu[i].x / pq, end = qu[i].y / pq;
			int result = 0;
			if (start == end) {
				for (int j = qu[i].x; j <= qu[i].y; j++) {
					if (input[j] > qu[i].k)
						result++;
				}
			}
			else {
				for (int j = qu[i].x; j < (start + 1) * pq; j++) {
					if (input[j] > qu[i].k)
						result++;
				}

				int index = std::lower_bound(X.begin(), X.end(), qu[i].k) - X.begin();
				for (int j = start + 1; j <= end - 1; j++) {
					result += query(j, index, X.size() - 1);
				}

				for (int j = end * pq; j <= qu[i].y; j++) {
					if (input[j] > qu[i].k)
						result++;
				}
			}

			printf("%d\n", result);
		}
		else {
			int prev = std::lower_bound(X.begin(), X.end(), input[qu[i].x]) - X.begin();
			if(prev != 0)
				update(qu[i].x / pq, prev - 1, -1);
			int next = std::lower_bound(X.begin(), X.end(), qu[i].k) - X.begin();
			if(next != 0)
				update(qu[i].x / pq, next - 1, 1);
			input[qu[i].x] = qu[i].k;
		}
	}
}