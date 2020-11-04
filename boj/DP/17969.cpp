#include <stdio.h>
#include <algorithm>
#include <vector>

struct node {
	long long hap, square, cnt;
	node(long long hap = 0, long long square = 0, long long cnt = 0) : hap(hap), square(square), cnt(cnt) {}
};

long long result;
std::vector<std::pair<int, int>> graph[100010];

node func(int p, int num) {
	if (p != -1 && graph[num].size() == 1) {
		return node(0, 0, 1);
	}

	node r, first, second;
	int ttmp = 0;

	for (int i = 0; i < graph[num].size(); i++) {
		if (graph[num][i].first == p)
			continue;

		if (ttmp == 0) {
			first = func(num, graph[num][i].first);
			first.square += graph[num][i].second * 2 * first.hap;
			first.square += first.cnt * graph[num][i].second * graph[num][i].second;
			first.hap += graph[num][i].second * first.cnt;
		}
		else {
			second = func(num, graph[num][i].first);
			second.square += graph[num][i].second * 2 * second.hap;
			second.square += second.cnt * graph[num][i].second * graph[num][i].second;
			second.hap += graph[num][i].second * second.cnt;
		}
		ttmp++;
	}

	if (p == -1) {
		result += first.square;
	}
	else {
		result += 2 * first.hap * second.hap;
		result += first.square * second.cnt;
		result += second.square * first.cnt;
		r.cnt = first.cnt + second.cnt;
		r.hap = first.hap + second.hap;
		r.square = first.square + second.square;
	}

	return r;
}

int main(void) {
	int n, root = 1;
	scanf("%d", &n);

	for (int i = 1; i < n; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		graph[a].push_back(std::make_pair(b, c));
		graph[b].push_back(std::make_pair(a, c));

		if (graph[a].size() == 1)
			root = a;
		if (graph[b].size() == 1)
			root = b;
	}

	func(-1, root);
	printf("%lld\n", result);
}