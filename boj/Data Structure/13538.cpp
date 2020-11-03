#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#define SIZE 524288

struct persistent_segment_tree {
	struct node {
		int l, r, value;
		node(int l, int r, int value) : l(l), r(r), value(value) {}
	};

	std::vector<node> nodelist;
	std::vector<int> root;

	void init(int _N) {
		root.resize(_N + 1, -1);
		root[0] = nodelist.size();
		nodelist.push_back(node(-1, -1, 0));
		init_tree(root[0], 0, SIZE - 1);
	}

	void init_tree(int x, int s, int e) {
		if (s == e) {
			nodelist[x].value = 0;
			return;
		}

		nodelist[x].l = nodelist.size();
		nodelist.push_back(node(-1, -1, 0));
		nodelist[x].r = nodelist.size();
		nodelist.push_back(node(-1, -1, 0));

		init_tree(nodelist[x].l, s, (s + e) / 2);
		init_tree(nodelist[x].r, (s + e) / 2 + 1, e);
	}

	void update(int i, int x, int value) {
		root[i] = update_node(root[i - 1], 0, SIZE - 1, x, value);
	}

	int update_node(int x, int s, int e, int goal, int value) {
		if (s > goal || e < goal)
			return x;

		if (s == e) {
			nodelist.push_back(node(-1, -1, nodelist[x].value + value));
			return nodelist.size() - 1;
		}

		int result = nodelist.size();
		nodelist.push_back(node(-1, -1, nodelist[x].value + value));
		nodelist[result].l = update_node(nodelist[x].l, s, (s + e) / 2, goal, value);
		nodelist[result].r = update_node(nodelist[x].r, (s + e) / 2 + 1, e, goal, value);

		return result;
	}

	int query(int i, int s, int e) {
		return query_node(root[i], 0, SIZE - 1, s, e);
	}

	int query_node(int x, int s, int e, int l, int r) {
		if (s > r || e < l)
			return 0;

		if (l <= s && e <= r)
			return nodelist[x].value;

		return query_node(nodelist[x].l, s, (s + e) / 2, l, r) + query_node(nodelist[x].r, (s + e) / 2 + 1, e, l, r);
	}
	
	int find(int l, int r, int value) {
		return find_node(root[l - 1], root[r], SIZE / 2, value);
	}

	int find_node(int lx, int rx, int range, int value) {
		if (range == 0) {
			return 0;
		}

		int num = value / range;
		int result = 0;
		int left = nodelist[nodelist[rx].l].value - nodelist[nodelist[lx].l].value;
		int right = nodelist[nodelist[rx].r].value - nodelist[nodelist[lx].r].value;

		if (num == 0) {
			if (right != 0)
				result = find_node(nodelist[lx].r, nodelist[rx].r, range / 2, value % range) + range;
			else
				result = find_node(nodelist[lx].l, nodelist[rx].l, range / 2, value % range);
		}
		else {
			if (left != 0)
				result = find_node(nodelist[lx].l, nodelist[rx].l, range / 2, value % range);
			else
				result = find_node(nodelist[lx].r, nodelist[rx].r, range / 2, value % range) + range;
		}

		return result;
	}
};

int main(void) {
	int q, finish = 0;
	persistent_segment_tree ptree;
	scanf("%d", &q);

	ptree.init(q);

	for (int i = 1; i <= q; i++) {
		int type;
		scanf("%d", &type);

		if (type == 1) {
			int x;
			scanf("%d", &x);
			finish++;
			ptree.update(finish, x, 1);
		}
		else if (type == 2) {
			int l, r, x;
			scanf("%d %d %d", &l, &r, &x);
			printf("%d\n", ptree.find(l, r, x));
		}
		else if (type == 3) {
			int k;
			scanf("%d", &k);

			finish -= k;
		}
		else if (type == 4) {
			int l, r, x;
			scanf("%d %d %d", &l, &r, &x);

			printf("%d\n", ptree.query(r, 0, x) - ptree.query(l - 1, 0, x));
		}
		else {
			int l, r, x;
			scanf("%d %d %d", &l, &r, &x);

			int s = 0, e = 500000, result = 0;

			while (s <= e) {
				int mid = (s + e) / 2;
				if (ptree.query(r, 0, mid) - ptree.query(l - 1, 0, mid) < x) {
					s = mid + 1;
					result = std::max(result, mid);
				}
				else
					e = mid - 1;
			}

			printf("%d\n", result + 1);
		}
	}
}