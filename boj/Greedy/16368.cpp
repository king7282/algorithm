#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 131072

std::vector<int> result[2010];
int works[2010], last[2010];
int lazy[SIZE * 2 + 1], tree[SIZE * 2 + 1], a[SIZE];

void init(int node, int start, int end) {
	lazy[node] = 0;
	if (start == end)
		tree[node] = a[start];
	else {
		init(node << 1, start, (start + end) >> 1);
		init((node << 1) | 1, ((start + end) >> 1) + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void lazy_propagation(int node, int start, int end) {
	if (lazy[node] != 0) {
		tree[node] += (end - start + 1) * lazy[node];
		if (start != end) {
			lazy[node << 1] += lazy[node];
			lazy[(node << 1) | 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(int node, int start, int end, int i, int j, long long val) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return;
	if (i <= start && end <= j) {
		tree[node] += (end - start + 1) * val;
		if (start != end) {
			lazy[node << 1] += val;
			lazy[(node << 1) | 1] += val;
		}
		return;
	}
	else {
		update(node << 1, start, (start + end) / 2, i, j, val);
		update((node << 1) | 1, (start + end) / 2 + 1, end, i, j, val);
		tree[node] = tree[node << 1] + tree[(node << 1) | 1];
	}
}

long long query(int node, int start, int end, int i, int j) {
	lazy_propagation(node, start, end);
	if (i > end || j < start)
		return 0;
	if (i <= start && end <= j)
		return tree[node];
	return query(node * 2, start, (start + end) / 2, i, j) + query(node * 2 + 1, (start + end) / 2 + 1, end, i, j);
}

int main(void) {
	int m, n, w, h;
	scanf("%d %d %d %d", &m, &n, &w, &h);
	bool flag = true;

	for (int i = 1; i <= m; i++) {
		int a;
		scanf("%d", &a);
		works[i] = a / w;
		if (a % w != 0)
			flag = false;
	}

	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);

	init(1, 0, SIZE - 1);
	for (int i = 1; i <= n && flag; i++) {
		int day = query(1, 0, SIZE - 1, i, i);
		if (day <= 0) {
			if (day < 0)
				flag = false;
			continue;
		}

		std::vector<std::pair<int, int>> qu;
		for (int j = 1; j <= m; j++) {
			if (last[j] < i && works[j] > 0) {
				qu.push_back(std::make_pair(works[j], j));
			}
		}

		std::sort(qu.begin(), qu.end());
		for (int j = qu.size() - 1; j >= 0 && day >= 1; j--, day--) {
			update(1, 0, SIZE - 1, i, i + w - 1, -1);
			works[qu[j].second]--;
			last[qu[j].second] = i + w - 1 + h;
			result[qu[j].second].push_back(i);
		}

		if (day != 0)
			flag = false;
	}

	if (flag) {
		printf("1\n");
		for (int i = 1; i <= m; i++) {
			for (int j = 0; j < result[i].size(); j++)
				printf("%d ", result[i][j]);
			printf("\n");
		}
	}
	else {
		printf("-1\n");
	}
}