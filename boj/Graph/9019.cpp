#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cassert>
#define MOD 10000

int visited[10010];
std::pair<char, int> prev[10010];

void func(int cur, int finish) {
	if (cur == finish)
		return;
	
	func(prev[cur].second, finish);
	printf("%c", prev[cur].first);
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		std::queue<int> qu;

		int s, e;
		scanf("%d %d", &s, &e);

		memset(visited, -1, sizeof(visited));
		qu.push(s);
		visited[s] = 0;

		while (!qu.empty()) {
			int front = qu.front();
			qu.pop();

			int D = (front * 2) % MOD, S = (front - 1 + MOD) % MOD, L = 0, R = 0;

			std::vector<int> digits;
			int tmp = front;
			for (int i = 0; i < 4; i++) {
				digits.push_back(tmp % 10);
				tmp /= 10;
			}

			std::reverse(digits.begin(), digits.end());

			L = digits[1] * 1000 + digits[2] * 100 + digits[3] * 10 + digits[0];
			R = digits[3] * 1000 + digits[0] * 100 + digits[1] * 10 + digits[2];

			if (visited[D] == -1) {
				visited[D] = visited[front] + 1;
				prev[D] = { 'D', front };
				if (D == e)
					break;
				qu.push(D);
			}
			if (visited[S] == -1) {
				visited[S] = visited[front] + 1;
				prev[S] = { 'S', front };
				if (S == e)
					break;
				qu.push(S);
			}
			if (visited[L] == -1) {
				visited[L] = visited[front] + 1;
				prev[L] = { 'L', front };
				if (L == e)
					break;
				qu.push(L);
			}
			if (visited[R] == -1) {
				visited[R] = visited[front] + 1;
				prev[R] = { 'R', front };
				if (R == e)
					break;
				qu.push(R);
			}
		}

		func(e, s);
		printf("\n");
	}
}