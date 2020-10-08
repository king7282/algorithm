#include <stdio.h>
#include <vector>
#include <algorithm>

struct info {
	int next, weight;
	info(int next, int weight) : next(next), weight(weight) {}
}; 

std::vector<info> graph[10010];
int result = 0;

int func(int num) {
	int max1 = 0, max2 = 0;

	for (int i = 0; i < graph[num].size(); i++) {
		int tmp = func(graph[num][i].next) + graph[num][i].weight;

		if (tmp >= max1) {
			max2 = max1;
			max1 = tmp;
		}
		else if (tmp >= max2) {
			max2 = tmp;
		}
	}

	result = std::max(result, max1 + max2);
	return max1;
}

int main(void) {
	int n;
	scanf("%d", &n);
	
	for (int i = 1; i < n; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		
		graph[a].push_back(info(b, c));
	}
	
	func(1);
	printf("%d\n", result);
}