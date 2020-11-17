#include <stdio.h>
#include <vector>
#include <algorithm>
#define START (1 << 29)

struct info {
	int l, r, cnt;
	info(int l, int r, int cnt) : l(l), r(r), cnt(cnt) {}
};

std::vector<info> nodelist;

void insert(int node, int value, int range) {
	nodelist[node].cnt++;
	if (range == 0)
		return;
	int tmp = value / range;

	if (tmp == 0) {
		if (nodelist[node].l == -1) {
			nodelist[node].l = nodelist.size();
			nodelist.push_back(info(-1, -1, 0));
		}

		insert(nodelist[node].l, value % range, range / 2);
	}
	else {
		if (nodelist[node].r == -1) {
			nodelist[node].r = nodelist.size();
			nodelist.push_back(info(-1, -1, 0));
		}
		insert(nodelist[node].r, value % range, range / 2);
	}
}

int func(int node) {
	if (nodelist[node].cnt == 1)
		return nodelist[node].cnt;

	if (nodelist[node].l == -1) {
		return func(nodelist[node].r);
	}
	else if (nodelist[node].r == -1) {
		return func(nodelist[node].l);
	}
	else {
		return std::max(func(nodelist[node].l), func(nodelist[node].r)) + 1;
	}
}

int input[200010];

int main(void) {
	int n;
	scanf("%d", &n);
	nodelist.push_back(info(-1, -1, 0));

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		insert(0, input[i], START);
	}

	int result = func(0);
	printf("%d\n", n - result);
}