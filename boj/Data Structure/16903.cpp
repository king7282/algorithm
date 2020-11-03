#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 1073741824

struct node {
	int l, r, value;
	node(int l, int r, int value) : l(l), r(r), value(value) {}
};

std::vector<node> nodelist;
int root;

void update(int x, int s, int e, int l, int r, int value) {
	if (l > e || r < s)
		return;

	if (l <= s && e <= r) {
		nodelist[x].value += value;
		return;
	}
	if (nodelist[x].l == -1) {
		nodelist[x].l = nodelist.size();
		nodelist.push_back(node(-1, -1, 0));
	}
	if (nodelist[x].r == -1) {
		nodelist[x].r = nodelist.size();
		nodelist.push_back(node(-1, -1, 0));
	}

	update(nodelist[x].l, s, (s + e) / 2, l, r, value);
	update(nodelist[x].r, (s + e) / 2 + 1, e, l, r, value);
	nodelist[x].value += value;
}

int query(int x, int value, int range) {
	if (range == 0) {
		return 0;
	}

	int left = 0, right = 0;
	if (nodelist[x].l != -1)
		left = nodelist[nodelist[x].l].value;
	if (nodelist[x].r != -1)
		right = nodelist[nodelist[x].r].value;

	int num = value / range;
	int result = 0;
	if (num == 0) {
		if (right != 0) {
			result = query(nodelist[x].r, value % range, range / 2) + range;
		}
		else {
			result = query(nodelist[x].l, value % range, range / 2);
		}
	}
	else {
		if (left != 0) {
			result = query(nodelist[x].l, value % range, range / 2) + range;
		}
		else {
			result = query(nodelist[x].r, value % range, range / 2);
		}
	}

	return result;
}

int main(void) {
	int n;
	scanf("%d", &n);
	root = nodelist.size();
	nodelist.push_back(node(-1, -1, 0));
	update(root, 0, SIZE - 1, 0, 0, 1);

	for (int i = 1; i <= n; i++) {
		int type, x;
		scanf("%d %d", &type, &x);

		if (type == 1) {
			update(root, 0, SIZE - 1, x, x, 1);
		}
		else if (type == 2) {
			update(root, 0, SIZE - 1, x, x, -1);
		}
		else {
			printf("%d\n", query(root, x, SIZE / 2));
		}
	}
}