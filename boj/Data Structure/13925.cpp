#include <stdio.h>
#include <algorithm>
#define MOD 1000000007LL

struct info {
	long long v, mul, add;
	info(long long v = 0, long long mul = 1, long long add = 0) : v(v), mul(mul), add(add) {}
};

info lazy[131072 * 2 + 1], tree[131072 * 2 + 1], a[131072];

void init(int node, int start, int end) {
	lazy[node] = info(0, 1, 0);
	if (start == end)
		tree[node] = a[start];
	else {
		init(node << 1, start, (start + end) >> 1);
		init((node << 1) | 1, ((start + end) >> 1) + 1, end);

		info left = tree[node << 1], right = tree[node << 1 | 1];
		tree[node] = info((left.v * left.mul % MOD + right.v * right.mul % MOD) % MOD, 1, (left.add + right.add) % MOD);
	}
}

void lazy_propagation(int node, int start, int end) {
	if (!(lazy[node].v == 0 && lazy[node].mul == 1 && lazy[node].add == 0)) {
		if (lazy[node].v != 0) {
			tree[node].v = lazy[node].v * (end - start + 1) % MOD;
			tree[node].mul = lazy[node].mul;
			tree[node].add = lazy[node].add * (end - start + 1) % MOD;
			if (start != end) {
				lazy[node << 1] = lazy[node];
				lazy[node << 1 | 1] = lazy[node];
			}
		}
		else {
			tree[node].mul = (tree[node].mul * lazy[node].mul) % MOD;
			tree[node].add = (tree[node].add * lazy[node].mul % MOD + lazy[node].add * (end - start + 1) % MOD) % MOD;
			if (start != end) {
				lazy[node << 1].mul = (lazy[node << 1].mul * lazy[node].mul) % MOD;
				lazy[node << 1].add = (lazy[node << 1].add * lazy[node].mul + lazy[node].add) % MOD;

				lazy[node << 1 | 1].mul = (lazy[node << 1 | 1].mul * lazy[node].mul) % MOD;
				lazy[node << 1 | 1].add = (lazy[node << 1 | 1].add * lazy[node].mul + lazy[node].add) % MOD;

			}
		}
		lazy[node] = info(0, 1, 0);
	}
}

void update(int node, int start, int end, int i, int j, info val) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return;
	if (i <= start && end <= j) {
		if (val.v != 0) {
			tree[node].v = val.v * (end - start + 1) % MOD;
			tree[node].mul = 1;
			tree[node].add = 0;
			if (start != end) {
				lazy[node << 1] = info(val.v, 1, 0);
				lazy[node << 1 | 1] = info(val.v, 1, 0);
			}
		}
		else if(val.mul > 1){
			tree[node].mul = (tree[node].mul * val.mul) % MOD;
			tree[node].add = (tree[node].add * val.mul) % MOD;
			if (start != end) {
				lazy[node << 1].mul = (lazy[node << 1].mul * val.mul) % MOD;
				lazy[node << 1].add = (lazy[node << 1].add * val.mul) % MOD;
				lazy[node << 1 | 1].mul = (lazy[node << 1 | 1].mul * val.mul) % MOD;
				lazy[node << 1 | 1].add = (lazy[node << 1 | 1].add * val.mul) % MOD;
			}
		}
		else {
			tree[node].add = (tree[node].add + val.add * (end - start + 1) % MOD) % MOD;
			if (start != end) {
				lazy[node << 1].add = (lazy[node << 1].add + val.add) % MOD;
				lazy[node << 1 | 1].add = (lazy[node << 1 | 1].add + val.add) % MOD;
			}
		}
		return;
	}
	else {
		update(node << 1, start, (start + end) / 2, i, j, val);
		update((node << 1) | 1, (start + end) / 2 + 1, end, i, j, val);

		info left = tree[node << 1], right = tree[node << 1 | 1];
		tree[node] = info((left.v * left.mul % MOD + right.v * right.mul % MOD) % MOD, 1, (left.add + right.add) % MOD);
	}
}

info query(int node, int start, int end, int i, int j) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return info(0, 1, 0);
	if (i <= start && end <= j)
		return tree[node];

	info left = query(node * 2, start, (start + end) / 2, i, j), right = query(node * 2 + 1, (start + end) / 2 + 1, end, i, j);
	return info((left.v * left.mul % MOD + right.v * right.mul % MOD) % MOD, 1, (left.add + right.add) % MOD);
}

int main(void) {
	int n;
	scanf("%d", &n);

	a[0].v = 0;
	a[0].mul = 1;
	a[0].add = 0;
	for (int i = 1; i <= n; i++) {
		long long tmp;
		scanf("%lld", &tmp);
		a[i].v = tmp;
		a[i].mul = 1;
		a[i].add = 0;
	}

	init(1, 0, n);

	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int type, x, y;
		long long v;
		scanf("%d %d %d", &type, &x, &y);

		if (type == 1) {
			scanf("%lld", &v);
			update(1, 0, n, x, y, info(0, 1, v));
		}
		else if (type == 2) {
			scanf("%lld", &v);
			update(1, 0, n, x, y, info(0, v, 0));
		}
		else if (type == 3) {
			scanf("%lld", &v);
			update(1, 0, n, x, y, info(v, 1, 0));
		}
		else {
			info result = query(1, 0, n, x, y);
			printf("%lld\n", (result.v * result.mul % MOD + result.add) % MOD);
		}
	}
}