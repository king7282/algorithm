#include <stdio.h>
#include <algorithm>
#include <queue>
#include <cstring>

int visited[200010], prev[200010];
std::queue<int> qu;

void trace(int cur) {
	if (visited[cur] == 0) {
		printf("%d ", cur);
		return;
	}

	trace(prev[cur]);
	printf("%d ", cur);
}
int main(void) {
	int s, e;
	scanf("%d %d", &s, &e);

	memset(visited, -1, sizeof(visited));
	qu.push(s);
	visited[s] = 0;

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();

		if (front < 200000 && visited[front + 1] == -1) {
			visited[front + 1] = visited[front] + 1;
			prev[front + 1] = front;

			qu.push(front + 1);
		}

		if (front > 0 && visited[front - 1] == -1) {
			visited[front - 1] = visited[front] + 1;
			prev[front - 1] = front;

			qu.push(front - 1);
		}

		if (front * 2 <= 200000 && visited[2 * front] == -1) {
			visited[2 * front] = visited[front] + 1;
			prev[2 * front] = front;

			qu.push(2 * front);
		}
	}
	
	printf("%d\n", visited[e]);

	trace(e);
}