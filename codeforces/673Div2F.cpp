#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#define SIZE 1048576

int tt[SIZE];
int node[SIZE];
int tree[SIZE * 2 + 1], tree1[SIZE], n, pivot;
int input[SIZE], reverse[SIZE];
std::pair<int, int> edges[SIZE], range[SIZE];
bool check[SIZE];
std::vector<int> graph[SIZE];

int find(int num) {
	if (tree1[num] == -1)
		return num;
	return tree1[num] = find(tree1[num]);
}

void update(int num, int val) {
	num |= SIZE;
	tree[num] = val;

	while (num >>= 1)
		tree[num] = std::max(tree[num << 1], tree[num << 1 | 1]);
}

int query(int s, int e) {
	s |= SIZE, e |= SIZE;
	int r = 0;

	while (s <= e) {
		if (s % 2 == 1) r = std::max(r, tree[s]);
		if (e % 2 == 0) r = std::max(r, tree[e]);

		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}

void func(int num) {
	pivot++;
	reverse[num] = pivot;
	if (1 <= num && num <= n) {
		update(pivot, input[num]);
	}

	int cur = pivot;
	range[cur].first = pivot;
	for (int i = 0; i < graph[num].size(); i++) {
		func(graph[num][i]);
	}
	range[cur].second = pivot;
}

int main(void) {
	int m, q;
	scanf("%d %d %d", &n, &m, &q);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		tt[input[i]] = i;
	}

	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &edges[i].first, &edges[i].second);
	}

	std::vector<std::pair<int, int>> rq;

	for (int i = 0; i < q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a == 2)
			check[b] = true;
		rq.push_back(std::make_pair(a, b));
	}

	for (int i = 1; i <= m; i++) {
		if (check[i] == false)
			rq.push_back(std::make_pair(2, i));
	}

	memset(tree1, -1, sizeof(tree1));
	int cnt = n;
	for (int i = rq.size() - 1; i >= 0; i--) {
		if (rq[i].first == 1) {
			node[i] = find(rq[i].second);
		}
		else {
			if (find(edges[rq[i].second].first) != find(edges[rq[i].second].second)) {
				cnt++;
				graph[cnt].push_back(find(edges[rq[i].second].first));
				graph[cnt].push_back(find(edges[rq[i].second].second));
				tree1[find(edges[rq[i].second].first)] = cnt;
				tree1[find(edges[rq[i].second].second)] = cnt;
			}
		}
	}

	cnt++;
	for (int i = 1; i < cnt; i++) {
		if (tree1[i] == -1) {
			tree1[i] = cnt;
			graph[cnt].push_back(i);
		}
	}

	func(cnt);
	for (int i = 0; i < rq.size(); i++) {
		if (rq[i].first == 1) {
			int result = query(range[reverse[node[i]]].first, range[reverse[node[i]]].second);
			printf("%d\n", result);
			if(result != 0)
				update(reverse[tt[result]], 0);
		}
	}

}