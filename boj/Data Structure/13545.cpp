#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>
#define SIZE 262144

struct info {
	int x, y, index;
	info(int x, int y, int index) : x(x), y(y), index(index) {}
};

int tree[SIZE * 2 + 1], first[SIZE], last[SIZE];
int result[100010], input[100010], pq = 1000;
std::vector<info> qu[1010];
std::vector<int> sum[SIZE];

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
	int n;
	scanf("%d", &n);

	sum[n].push_back(0);
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		input[i] = input[i - 1] + a;
		sum[input[i] + n].push_back(i);
	}

	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--;

		qu[a / pq].push_back(info(a, b, i));
	}

	for (int i = 0; i <= (n - 1) / pq; i++) {
		if (qu[i].size() == 0)
			continue;

		std::sort(qu[i].begin(), qu[i].end(), [](info a, info b) {
			if (a.y == b.y)
				return a.x > b.x;
			return a.y < b.y;
			});

		memset(tree, 0, sizeof(tree));

		for (int j = 0; j <= 2 * n; j++) {
			if (sum[j].size() == 0)
				continue;

			int s = 0, e = sum[j].size() - 1, r = sum[j].size();

			while (s <= e) {
				int mid = (s + e) / 2;
				if (sum[j][mid] >= qu[i][0].x) {
					e = mid - 1;
					r = std::min(mid, r);
				}
				else
					s = mid + 1;
			}

			first[j] = r;

			s = 0, e = sum[j].size() - 1, r = -1;
			while (s <= e) {
				int mid = (s + e) / 2;
				if (sum[j][mid] <= qu[i][0].y) {
					s = mid + 1;
					r = std::max(r, mid);
				}
				else
					e = mid - 1;
			}

			last[j] = r;

			if (last[j] >= first[j])
				update(j, std::max(0, sum[j][last[j]] - sum[j][first[j]]));
		}

		result[qu[i][0].index] = query(0, 2 * n);
		for (int j = 1; j < qu[i].size(); j++) {
			for (int k = qu[i][j - 1].y + 1; k <= qu[i][j].y; k++) {
				int tmp = input[k] + n;
				last[tmp]++;
				if (last[tmp] > first[tmp])
					update(tmp, std::max(0, sum[tmp][last[tmp]] - sum[tmp][first[tmp]]));
				else
					update(tmp, 0);
			}

			for (int k = std::min(qu[i][j - 1].x, qu[i][j].x); k <= std::max(qu[i][j - 1].x, qu[i][j].x); k++) {
				int tmp = input[k] + n;
				int s = 0, e = sum[tmp].size() - 1, r = sum[tmp].size();

				while (s <= e) {
					int mid = (s + e) / 2;
					if (sum[tmp][mid] >= qu[i][j].x) {
						r = std::min(r, mid);
						e = mid - 1;
					}
					else
						s = mid + 1;
				}
				first[tmp] = r;

				if (last[tmp] > first[tmp])
					update(tmp, std::max(0, sum[tmp][last[tmp]] - sum[tmp][first[tmp]]));
				else
					update(tmp, 0);
			}

			result[qu[i][j].index] = query(0, 2 * n);
		}
	}


	for (int i = 1; i <= q; i++) {
		printf("%d\n", result[i]);
	}
}