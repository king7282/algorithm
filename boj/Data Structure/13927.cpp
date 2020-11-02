#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

struct inner {
	int l, r, value;
	inner(int l = -1, int r = -1, int value = 0) : l(l), r(r), value(value) {}
};

struct outer {
	int l, r, in;
	outer(int l = -1, int r = -1, int in = -1) : l(l), r(r), in(in) {}
};

int input[100010], back[100010], root[100010], n;
std::vector<outer> outerlist;
std::vector<inner> innerlist;
std::vector<int> X;

void init(int x, int s, int e) {
	if (s == e) {
		return;
	}

	outerlist[x].l = outerlist.size();
	outerlist.push_back(outer(-1, -1, -1));
	outerlist[x].r = outerlist.size();
	outerlist.push_back(outer(-1, -1, -1));

	init(outerlist[x].l, s, (s + e) / 2);
	init(outerlist[x].r, (s + e) / 2 + 1, e);
}

int update_inner(int x, int s, int e, int goal, int value) {
	if (goal > e || goal < s)
		return x;

	int real = value, left = -1, right = -1;
	if (x != -1) {
		real += innerlist[x].value;
		left = innerlist[x].l;
		right = innerlist[x].r;
	}

	if (s == e) {
		innerlist.push_back(inner(-1, -1, real));
		return innerlist.size() - 1;
	}

	int result = innerlist.size();
	innerlist.push_back(inner(-1, -1, real));
	innerlist[result].l = update_inner(left, s, (s + e) / 2, goal, value);
	innerlist[result].r = update_inner(right, (s + e) / 2 + 1, e, goal, value);

	return result;
}

int update_outer(int x, int s, int e, int goal, int in, int value) {
	if (goal > e || goal < s)
		return x;

	if (s == e) {
		outerlist.push_back(outer(-1, -1, update_inner(outerlist[x].in, 0, X.size(), in, value)));
		return outerlist.size() - 1;
	}

	int result = outerlist.size();
	outerlist.push_back(outer(-1, -1, update_inner(outerlist[x].in, 0, X.size(), in, value)));
	outerlist[result].l = update_outer(outerlist[x].l, s, (s + e) / 2, goal, in, value);
	outerlist[result].r = update_outer(outerlist[x].r, (s + e) / 2 + 1, e, goal, in, value);
	return result;
}

int query_inner(int x, int s, int e, int l, int r) {
	if (l > r)
		return 0;

	if (l > e || r < s || x == -1)
		return 0;

	if (l <= s && e <= r) {
		return innerlist[x].value;
	}

	return query_inner(innerlist[x].l, s, (s + e) / 2, l, r) + query_inner(innerlist[x].r, (s + e) / 2 + 1, e, l, r);
}

int query_outer(int x, int s, int e, int l, int r, int inners, int innery) {
	if (l > r)
		return 0;

	if (l > e || r < s)
		return 0;

	if (l <= s && e <= r) {
		return query_inner(outerlist[x].in, 0, X.size(), inners, innery);
	}

	return query_outer(outerlist[x].l, s, (s + e) / 2, l, r, inners, innery) + query_outer(outerlist[x].r, (s + e) / 2 + 1, e, l, r, inners, innery);
}

bool OK(int l, int r, int k, int num) {
	if (num == 0) {
		return true;
	}

	int result = query_outer(root[r], 0, n, 0, n, 0, num - 1) - query_outer(root[r], 0, n, l, r, 0, num - 1);
	if (l > 1) {
		result -= query_outer(root[l - 1], 0, n, 0, n, 0, num - 1);
	}

	return result < k;
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		X.push_back(input[i]);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	memset(root, -1, sizeof(root));
	root[1] = outerlist.size();
	outerlist.push_back(outer(-1, -1, -1));
	init(root[1], 0, n);

	std::vector<std::pair<int, int>> points;

	for (int i = 1; i <= n; i++) {
		input[i] = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
		if (root[i] == -1)
			root[i] = root[i - 1];

		root[i] = update_outer(root[i], 0, n, back[input[i]], input[i], 1);
		back[input[i]] = i;
	}
	
	int q;
	long long ans = 0;
	scanf("%d", &q);
	
	for (int i = 1; i <= q; i++) {
		long long a, b, c, d, k;
		scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &k);

		int l = (a * std::max(ans, 0LL) + b) % n + 1, r = (c * std::max(ans, 0LL) + d) % n + 1;

		if (l > r)
			std::swap(l, r);
		
		int s = 0, e = X.size(), result = 0;
		while (s <= e) {
			int mid = (s + e) / 2;

			if (OK(l, r, k, mid)) {
				s = mid + 1;
				result = std::max(result, mid);
			}
			else
				e = mid - 1;
		}

		if (result == X.size())
			ans = -1;
		else
			ans = X[result];

		printf("%lld\n", ans);
	}
}