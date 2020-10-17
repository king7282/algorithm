#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <list>

struct info {
	int x, y, index;
	info(int x, int y, int index) : x(x), y(y), index(index) {}
};

int tree[210], index1[110010], index2[110010];
int result[110010], input[110010], pq = 500;
std::vector<info> qu;

void update(int val) {
	tree[index1[val] / pq]--;
	index2[index1[val]]--;
	index1[val]++;
	index2[index1[val]]++;
	tree[index1[val] / pq]++;
}

void remove(int val) {
	tree[index1[val] / pq]--;
	index2[index1[val]]--;
	index1[val]--;
	index2[index1[val]]++;
	tree[index1[val] / pq]++;
}

int main(void) {
	int n;
	scanf("%d", &n);
	std::vector<int> X;

	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", input + i);
		X.push_back(input[i]);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	for (int i = 0; i < n; i++) {
		input[i] = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
		tree[0]++;
		index2[0]++;
	}

	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--;
		b--;

		qu.push_back(info(a, b, i));
	}

	std::sort(qu.begin(), qu.end(), [&](info a, info b) {
		int ai = a.x / pq, bi = b.x / pq;
		if (ai == bi)
			return a.y < b.y;
		return ai < bi;
		});

	for (int j = qu[0].x; j <= qu[0].y; j++) {
		update(input[j]);
	}

	for (int i = 200; i >= 0; i--) {
		if (tree[i] > 0) {
			for (int j = i * pq; j < (i + 1) * pq; j++) {
				if (index2[j] > 0)
					result[qu[0].index] = std::max(result[qu[0].index], j);
			}
			break;
		}
	}

	for (int j = 1; j < qu.size(); j++) {
		if (qu[j - 1].y <= qu[j].y) {
			for (int k = qu[j - 1].y + 1; k <= qu[j].y; k++) {
				update(input[k]);
			}
		}
		else {
			for (int k = qu[j - 1].y; k > qu[j].y; k--) {
				remove(input[k]);
			}
		}
		if (qu[j - 1].x < qu[j].x) {
			for (int k = qu[j - 1].x; k < qu[j].x; k++) {
				remove(input[k]);
			}
		}
		else {
			for (int k = qu[j - 1].x - 1; k >= qu[j].x; k--) {
				update(input[k]);
			}
		}

		for (int i = 200; i >= 0; i--) {
			if (tree[i] > 0) {
				for (int k = i * pq; k < (i + 1) * pq; k++) {
					if (index2[k] > 0)
						result[qu[j].index] = std::max(result[qu[j].index], k);
				}
				break;
			}
		}
	}


	for (int i = 1; i <= q; i++) {
		printf("%d\n", result[i]);
	}
}