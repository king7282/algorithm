#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#define SIZE 131072

struct info {
	int x, y, index;
	info(int x, int y, int index) : x(x), y(y), index(index) {}
};

long long result[SIZE];
int input[SIZE], pq = 1200;
std::vector<info> qu;

template <typename T>
class FenwickTree {
public:
	int size;
	std::vector<T> arr;
	std::vector<T> data;

	FenwickTree<T>(int _N) {
		size = _N;
		arr.resize(size + 1);
		data.resize(size + 1);
	}

	void update(int x, T val) {
		T delta_val = val - arr[x];
		arr[x] = val;

		while (x <= size) {
			data[x] += delta_val;
			x += (x&-x);
		}
	}
	T sum(int x) {
		T ret = 0;
		while (x) {
			ret += data[x];
			x &= x - 1;
		}
		return ret;
	}
	T sum(int x, int y) {
		return sum(y) - sum(x - 1);
	}
};

int main(void) {
	int n, k1;
	scanf("%d %d", &n, &k1);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
	}

	FenwickTree<int> tree(100000);

	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		qu.push_back(info(a, b, i));
	}

	std::sort(qu.begin(), qu.end(), [&](info a, info b) {
		int ai = a.x / pq, bi = b.x / pq;
		if (ai == bi)
			return a.y < b.y;
		return ai < bi;
	});

	for (int j = qu[0].x; j <= qu[0].y; j++) {
		result[qu[0].index] += tree.sum(std::max(1, input[j] - k1), std::min(100000, input[j] + k1));
		tree.update(input[j], tree.arr[input[j]] + 1);
	}

	for (int j = 1; j < qu.size(); j++) {
		result[qu[j].index] = result[qu[j - 1].index];
		if (qu[j - 1].y <= qu[j].y) {
			for (int k = qu[j - 1].y + 1; k <= qu[j].y; k++) {
				result[qu[j].index] += tree.sum(std::max(1, input[k] - k1), std::min(100000, input[k] + k1));
				tree.update(input[k], tree.arr[input[k]] + 1);
			}
		}
		else {
			for (int k = qu[j - 1].y; k > qu[j].y; k--) {
				tree.update(input[k], tree.arr[input[k]] - 1);
				result[qu[j].index] -= tree.sum(std::max(1, input[k] - k1), std::min(100000, input[k] + k1));
			}
		}
		if (qu[j - 1].x < qu[j].x) {
			for (int k = qu[j - 1].x; k < qu[j].x; k++) {
				tree.update(input[k], tree.arr[input[k]] - 1);
				result[qu[j].index] -= tree.sum(std::max(1, input[k] - k1), std::min(100000, input[k] + k1));
			}
		}
		else {
			for (int k = qu[j - 1].x - 1; k >= qu[j].x; k--) {
				result[qu[j].index] += tree.sum(std::max(1, input[k] - k1), std::min(100000, input[k] + k1));
				tree.update(input[k], tree.arr[input[k]] + 1);
			}
		}
	}

	for (int i = 1; i <= q; i++) {
		printf("%lld\n", result[i]);
	}
}