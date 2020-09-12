#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>
 
std::vector<int> graph[100010];
int min1, t1, t2, n;
 
int func(int p, int num) {
	int sum = 0, val = 0;
	for (int i = 0; i < graph[num].size(); i++) {
		if (p == graph[num][i])
			continue;
		int tmp = func(num, graph[num][i]);
		sum += tmp;
		val = std::max(val, tmp);
	}
 
	val = std::max(val, n - sum - 1);
	if (min1 > val) {
		min1 = val;
		t1 = num;
		t2 = -1;
	}
	else if (min1 == val) {
		t2 = num;
	}
	return sum + 1;
}
 
int func2(int p, int num) {
	for (int i = 0; i < graph[num].size(); i++) {
		if (p == graph[num][i])
			continue;
 
		return func2(num, graph[num][i]);
	}
 
	return num;
}
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		scanf("%d", &n);
 
		for (int i = 1; i < n; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		t1 = t2 = -1;
		min1 = INT_MAX / 2;
		func(0, 1);
 
		if (t2 == -1) {
			printf("%d %d\n", 1, graph[1][0]);
			printf("%d %d\n", 1, graph[1][0]);
		}
		else {
			int node = func2(t2, t1);
			printf("%d %d\n", node, graph[node][0]);
			printf("%d %d\n", t2, node);
		}
 
		for (int i = 1; i <= n; i++)
			graph[i].clear();
	}
}