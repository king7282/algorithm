#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 131072

struct info {
	int x, y, k, index;
	info(int x, int y, int k, int index) : x(x), y(y), k(k), index(index) {}
};

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

std::vector<info> qu;
int a[100010], b[100010], pq = 1000;
long long result[100010];

int ssqrt(long long num) {
	long long s = 0, e = num, r = 0;

	while (s <= e) {
		long long mid = (s + e) / 2;
		if (mid * mid <= num) {
			r = std::max(r, mid);
			s = mid + 1;
		}
		else
			e = mid - 1;
	}

	return r;
}

int main(void) {
	int n;
	FenwickTree<int> A(SIZE * 2), B(SIZE * 2);
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}

	for (int i = 1; i <= n; i++) {
		scanf("%d", b + i);
	}

	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (!(1 <= a && a <= SIZE && 1 <= b && b <= SIZE))
			while (1);
		qu.push_back(info(a, b, c, i));
	}

	std::sort(qu.begin(), qu.end(), [&](info a, info b) {
		if (a.x / pq == b.x / pq)
			return a.y < b.y;
		return a.x / pq < b.x / pq;
	});

	for (int i = qu[0].x; i <= qu[0].y; i++) {
		A.update(a[i], A.sum(a[i], a[i]) + 1);
		B.update(b[i], B.sum(b[i], b[i]) + 1);
	}

	int limits = ssqrt(qu[0].k);

	result[qu[0].index] = (long long)A.sum(1, limits) * B.sum(1, limits);
	for (int i = 1; i <= limits; i++) {
		if (limits + 1 <= qu[0].k / i) {
			result[qu[0].index] += (long long)A.sum(limits + 1, qu[0].k / i) * B.sum(i, i);
			result[qu[0].index] += (long long)B.sum(limits + 1, qu[0].k / i) * A.sum(i, i);
		}
		else
			break;
	}

	for (int i = 1; i < qu.size(); i++) {
		if (qu[i - 1].y < qu[i].y) {
			for (int j = qu[i - 1].y + 1; j <= qu[i].y; j++) {
				A.update(a[j], A.sum(a[j], a[j]) + 1);
				B.update(b[j], B.sum(b[j], b[j]) + 1);
			}
		}
		else {
			for (int j = qu[i - 1].y; j > qu[i].y; j--) {
				A.update(a[j], A.sum(a[j], a[j]) - 1);
				B.update(b[j], B.sum(b[j], b[j]) - 1);
			}
		}

		if (qu[i - 1].x < qu[i].x) {
			for (int j = qu[i - 1].x; j < qu[i].x; j++) {
				A.update(a[j], A.sum(a[j], a[j]) - 1);
				B.update(b[j], B.sum(b[j], b[j]) - 1);
			}
		}
		else {
			for (int j = qu[i].x; j < qu[i - 1].x; j++) {
				A.update(a[j], A.sum(a[j], a[j]) + 1);
				B.update(b[j], B.sum(b[j], b[j]) + 1);
			}
		}

		limits = ssqrt(qu[i].k);
		result[qu[i].index] = (long long)A.sum(1, limits) * B.sum(1, limits);
		for (int j = 1; j <= limits; j++) {
			if (limits + 1 <= qu[i].k / j) {
				result[qu[i].index] += (long long)A.sum(limits + 1, qu[i].k / j) * B.sum(j, j);
				result[qu[i].index] += (long long)B.sum(limits + 1, qu[i].k / j) * A.sum(j, j);
			}
			else
				break;
		}
	}
	

	for (int i = 1; i <= q; i++)
		printf("%lld\n", result[i]);
}