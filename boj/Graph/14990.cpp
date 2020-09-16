#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

struct info {
	int next, cap, index;
	info(int next, int cap, int index) : next(next), cap(cap), index(index) {}
};

struct node {
	int x, y, cap;
};

node input[1010];
std::vector<info> graph[1010];
bool visits[1010], visits2[1010];
int n, m;

bool OK(int num) {
	memset(visits, false, sizeof(visits));

	std::queue<int> qu;
	qu.push(0);

	visits[0] = true;
	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();

		for (int i = 0; i < graph[front].size(); i++) {
			if (graph[front][i].cap < num)
				continue;

			if (visits[graph[front][i].next] == false) {
				visits[graph[front][i].next] = true;
				qu.push(graph[front][i].next);
			}
		}
	}

	return visits[n - 1];
}

bool func(int num, int r) {
	visits2[num] = visits[num] = true;

	if (num == n - 1)
		return true;

	for (int i = 0; i < graph[num].size(); i++) {
		if (graph[num][i].cap < r)
			continue;

		if (visits2[graph[num][i].next] == false) {
			if (func(graph[num][i].next, r))
				return true;
		}
	}

	visits[num] = false;
	return false;
}

int main(void) {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &input[i].x, &input[i].y, &input[i].cap);
		graph[input[i].x].push_back(info(input[i].y, input[i].cap, i));
		graph[input[i].y].push_back(info(input[i].x, input[i].cap, i));
	}

	int s = 1, e = 500000, r = 1;

	while (s <= e) {
		int mid = (s + e) / 2;

		if (OK(mid)) {
			s = mid + 1;
			r = std::max(r, mid);
		}
		else
			e = mid - 1;
	}

	memset(visits, false, sizeof(visits));
	func(0, r);

	std::vector<int> result;
	for (int i = 0; i < n; i++) {
		if (visits[i] == true) {
			for (int j = 0; j < graph[i].size(); j++) {
				if (graph[i][j].cap < r || visits[graph[i][j].next] == false) {
					result.push_back(graph[i][j].index);
				}
			}
		}
	}
	std::sort(result.begin(), result.end());
	result.erase(std::unique(result.begin(), result.end()), result.end());

	if (result.size() == 0)
		printf("none\n");
	else {
		for (int i = 0; i < result.size(); i++)
			printf("%d ", result[i] - 1);
		printf("\n");
	}
}