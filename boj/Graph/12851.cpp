#include <stdio.h>
#include <algorithm>
#include <queue>
#include <cstring>

int visited[200010];
long long cnt[200010];

int main(void) {
	int s, e;
	scanf("%d %d", &s, &e);
	
	memset(visited, -1, sizeof(visited));
	std::queue<int> qu;
	qu.push(s);
	visited[s] = 0;
	cnt[s] = 1;

	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();

		if (front < 200000) {
			if (visited[front + 1] == -1) {
				visited[front + 1] = visited[front] + 1;
				qu.push(front + 1);
			}
			if (visited[front + 1] == visited[front] + 1)
				cnt[front + 1] += cnt[front];
		}

		if (front > 0) {
			if (visited[front - 1] == -1) {
				visited[front - 1] = visited[front] + 1;
				qu.push(front - 1);
			}

			if (visited[front - 1] == visited[front] + 1)
				cnt[front - 1] += cnt[front];
		}

		if (front * 2 <= 200000) {
			if (visited[front * 2] == -1) {
				visited[front * 2] = visited[front] + 1;
				qu.push(front * 2);
			}

			if (visited[front * 2] == visited[front] + 1)
				cnt[front * 2] += cnt[front];
		}
	}

	printf("%d\n%lld\n", visited[e], cnt[e]);
}