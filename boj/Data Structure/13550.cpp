#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <list>

struct info {
	int x, y, index;
	info(int x, int y, int index) : x(x), y(y), index(index) {}
};

int tree[210], index1[110010];
int result[110010], input[110010], pq = 500;
std::vector<info> qu;
std::list<int> sum[110010];

void update(int val) {
	tree[val / pq]++;
	index1[val]++;
}

void remove(int val) {
	tree[val/ pq]--;
	index1[val]--;
}

int main(void) {
	int n, k1;
	scanf("%d %d", &n, &k1);
	std::vector<int> X;
	int sum1 = 0;
	X.push_back(0);
	input[0] = 0;

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		sum1 = (sum1 + a) % k1;
		input[i] = sum1;
		X.push_back(input[i]);

	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	for (int i = 0; i <= n; i++) {
		input[i] = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
	}

	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--;

		qu.push_back(info(a, b, i));
	}

	std::sort(qu.begin(), qu.end(), [&](info a, info b) {
		int ai = a.x / pq, bi = b.x / pq;
		if (ai == bi)
			return a.y < b.y;
		return ai < bi;
		});

	for (int j = qu[0].x; j <= qu[0].y; j++) {
		if (sum[input[j]].size() > 0)
			remove(sum[input[j]].back() - sum[input[j]].front());
		sum[input[j]].push_back(j);
		update(sum[input[j]].back() - sum[input[j]].front());
	}

	for (int i = 200; i >= 0; i--) {
		if (tree[i] > 0) {
			for (int j = i * pq; j < (i + 1) * pq; j++) {
				if (index1[j] > 0)
					result[qu[0].index] = std::max(result[qu[0].index], j);
			}
			break;
		}
	}

	for (int j = 1; j < qu.size(); j++) {
		if (qu[j - 1].y <= qu[j].y) {
			for (int k = qu[j - 1].y + 1; k <= qu[j].y; k++) {
				if(sum[input[k]].size() > 0)
					remove(sum[input[k]].back() - sum[input[k]].front());
				sum[input[k]].push_back(k);
				update(sum[input[k]].back() - sum[input[k]].front());
			}
		}
		else {
			for (int k = qu[j - 1].y; k > qu[j].y; k--) {
				remove(sum[input[k]].back() - sum[input[k]].front());
				sum[input[k]].pop_back();
				if(sum[input[k]].size() > 0)
					update(sum[input[k]].back() - sum[input[k]].front());
			}
		}
		if (qu[j - 1].x < qu[j].x) {
			for (int k = qu[j - 1].x; k < qu[j].x; k++) {
				remove(sum[input[k]].back() - sum[input[k]].front());
				sum[input[k]].pop_front();
				if (sum[input[k]].size() > 0)
					update(sum[input[k]].back() - sum[input[k]].front());
			}
		}
		else {
			for (int k = qu[j - 1].x - 1; k >= qu[j].x; k--) {
				if (sum[input[k]].size() > 0)
					remove(sum[input[k]].back() - sum[input[k]].front());
				sum[input[k]].push_front(k);
				update(sum[input[k]].back() - sum[input[k]].front());
			}
		}

		for (int i = 200; i >= 0; i--) {
			if (tree[i] > 0) {
				for (int k = i * pq; k < (i + 1) * pq; k++) {
					if (index1[k] > 0)
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