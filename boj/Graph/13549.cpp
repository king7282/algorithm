#include <stdio.h>
#include <queue>
#include <cstring>

std::deque<int> qu;
int visited[200010];

int main(void) {
	int s, e;

	scanf("%d %d", &s, &e);

	memset(visited, -1, sizeof(visited));
	visited[s] = 0;
	qu.push_back(s);

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop_front();

		if (2 * front <= 200000 && visited[front * 2] == -1) {
			visited[front * 2] = visited[front];
			qu.push_front(front * 2);
		}

		if (front + 1 <= 200000 && visited[front + 1] == -1) {
			visited[front + 1] = visited[front] + 1;
			qu.push_back(front + 1);
		}

		if (front - 1 >= 0 && visited[front - 1] == -1) {
			visited[front - 1] = visited[front] + 1;
			qu.push_back(front - 1);
		}
	}

	printf("%d\n", visited[e]);
}