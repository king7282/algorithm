#include <stdio.h>
#include <algorithm>
#include <vector>

bool check[100010];
std::vector<int> graph[100010];
int result = 0, n, k;

int func(int p, int node) {
	bool flag = false;
	int cnt = 0;

	for (int i = 0; i < graph[node].size(); i++) {
		if (graph[node][i] == p)
			continue;

		int tmp = func(node, graph[node][i]);
		if (tmp != 0 && tmp != k) {
			flag = true;
		}
		cnt += tmp;
	}

	if (check[node] == true || flag == true)
		result++;

	if (check[node] == true)
		cnt++;

	return cnt;
}

int main(void) {
	scanf("%d %d", &n, &k);

	for (int i = 1; i < n; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 1; i <= k; i++) {
		int a;
		scanf("%d", &a);
		check[a] = true;
	}

	func(0, 1);
	printf("%d\n", result);
}