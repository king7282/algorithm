#include <stdio.h>
#include <queue>
#include <cstring>

std::queue<int> qu;
int visited[1000001];

int main(void) {
	int n, s, e, u, d;
	scanf("%d %d %d %d %d", &n, &s, &e, &u, &d);

	memset(visited, -1, sizeof(visited));
	visited[s] = 0;
	qu.push(s);

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();

		if (front + u <= n && visited[front + u] == -1) {
			visited[front + u] = visited[front] + 1;
			qu.push(front + u);
		}

		if (front - d >= 1 && visited[front - d] == -1) {
			visited[front - d] = visited[front] + 1;
			qu.push(front - d);
		}
	}

	if (visited[e] == -1)
		printf("use the stairs\n");
	else
		printf("%d\n", visited[e]);
}
