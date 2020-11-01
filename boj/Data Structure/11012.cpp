#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

struct node {
	int l, r, value;
	node(int l = -1, int r = -1, int value = 0) : l(l), r(r), value(value) {}
};

std::pair<int, int> input[100010];
std::vector<node> nodelist;
int root[100010];

void init(int x, int s, int e) {
	if (s == e) {
		nodelist[x].value = 0;
		return;
	}

	nodelist[x].l = nodelist.size();
	nodelist.push_back(node(-1, -1, 0));
	nodelist[x].r = nodelist.size();
	nodelist.push_back(node(-1, -1, 0));

	init(nodelist[x].l, s, (s + e) / 2);
	init(nodelist[x].r, (s + e) / 2 + 1, e);
}

int update(int x, int s, int e, int num, int value) {
	if (!(s <= num && num <= e))
		return x;
	
	if (s == e) {
		nodelist.push_back(node(-1, -1, value + nodelist[x].value));
		return nodelist.size() - 1;
	}

	nodelist.push_back(node(nodelist[x].l, nodelist[x].r, nodelist[x].value + value));
	int result = nodelist.size() - 1;
	nodelist[result].l = update(nodelist[x].l, s, (s + e) / 2, num, value);
	nodelist[result].r = update(nodelist[x].r, (s + e) / 2 + 1, e, num, value);

	return result;
}

int query(int x, int s, int e, int l, int r) {
	if (l > e || r < s)
		return 0;

	if (l <= s && e <= r) {
		return nodelist[x].value;
	}

	return query(nodelist[x].l, s, (s + e) / 2, l, r) + query(nodelist[x].r, (s + e) / 2 + 1, e, l, r);
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n, m, maxx = 0, maxy = 0;
		scanf("%d %d", &n, &m);

		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &input[i].first, &input[i].second);
			maxx = std::max(maxx, input[i].first);
			maxy = std::max(maxy, input[i].second);
		}

		std::sort(input + 1, input + 1 + n);
		nodelist.clear();
		memset(root, -1, sizeof(root));

		root[0] = nodelist.size();
		nodelist.push_back(node(-1, -1, 0));

		init(root[0], 0, maxy);
		int index = 1;

		for (int i = 0; i <= maxx; i++) {
			if (root[i] == -1)
				root[i] = root[i - 1];

			while (index <= n && input[index].first == i) {
				root[i] = update(root[i], 0, maxy, input[index].second, 1);
				index++;
			}
		}

		long long r = 0;
		for (int i = 1; i <= m; i++) {
			int xs, xr, ys, yr;
			scanf("%d %d %d %d", &xs, &xr, &ys, &yr);
			if (maxx < xs || maxy < ys)
				continue;

			xr = std::min(xr, maxx);
			yr = std::min(yr, maxy);

			int result = query(root[xr], 0, maxy, ys, yr);
			if (xs != 0)
				result -= query(root[xs - 1], 0, maxy, ys, yr);
			r += result;
		}
		printf("%lld\n", r);
	}
}