#include <stdio.h>
#include <vector>
#include <algorithm>

std::vector<int> graph[100010], leaf[100010], X;
std::vector<std::pair<int, int>> result;
bool check[100010];

void func(int p, int num) {
	if (graph[num].size() == 1) {
		X.push_back(num);
	}

	for (int i = 0; i < graph[num].size(); i++) {
		if (graph[num][i] == p)
			continue;

		func(num, graph[num][i]);
	}
}

int main(void) {
	int n, start;
	scanf("%d %d", &n, &start);

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	func(-1, start);

	for (int i = 0; i < X.size() / 2; i++) {
		result.push_back(std::make_pair(X[i], X[i + X.size() / 2]));
	}

	if (X.size() % 2 == 1)
		result.push_back(std::make_pair(X[0], X.back()));

	printf("%d\n", result.size());
	for (int i = 0; i < result.size(); i++) {
		if (result.size() - 1 != i) {
			printf("%d %d\n", result[i].first, result[i].second);
		}
		else
			printf("%d %d", result[i].first, result[i].second);
	}
} 