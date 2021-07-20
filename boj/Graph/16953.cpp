#include <stdio.h>
#include <map>
#include <algorithm>
#include <queue>

std::map<int, int> map;

int main(void) {
	int s, e;

	scanf("%d %d", &s, &e);

	std::queue<int> qu;

	qu.push(e);
	map[e] = 1;

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();

		if (front % 10 == 1 && 0 < front / 10 && map.find(front / 10) == map.end()) {
			map[front / 10] = map[front] + 1;
			qu.push(front / 10);
		}

		if (front % 2 == 0 && 0 < front / 2 && map.find(front / 2) == map.end()) {
			map[front / 2] = map[front] + 1;
			qu.push(front / 2);
		}

	}

	if (map.find(s) == map.end())
		printf("-1\n");
	else
		printf("%d\n", map[s]);

}
