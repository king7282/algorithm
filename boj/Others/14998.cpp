#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>
#define SIZE 8LL

long long mov[8][2] = { {-2, 1}, {-2, -1}, {2, 1}, {2, -1}, {1, -2}, {1, 2}, {-1, -2}, {-1, 2} };
long long visits[2 * SIZE + 1][2 * SIZE + 1];
std::queue<std::pair<int, int>> qu;

long long aabs(long long num) {
	if (num < 0)
		return num * -1;
	return num;
}

int main(void) {
	long long n, m, kx, ky, cx, cy;
	scanf("%lld %lld %lld %lld %lld %lld", &n, &m, &kx, &ky, &cx, &cy);
	memset(visits, -1, sizeof(visits));

	if (n <= SIZE * 2 && m <= SIZE * 2) {
		visits[kx][ky] = 0;
		qu.push(std::make_pair(kx, ky));

		while (!qu.empty()) {
			std::pair<int, int> front = qu.front();
			qu.pop();

			for (int i = 0; i < 8; i++) {
				int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

				if (!(0 <= nx && nx < n && 0 <= ny && ny < m))
					continue;

				if (visits[nx][ny] != -1)
					continue;

				visits[nx][ny] = visits[front.first][front.second] + 1;
				qu.push(std::make_pair(nx, ny));
			}
		}
		printf("%d\n", visits[cx][cy]);
	}
	else {
		visits[SIZE][SIZE] = 0;
		qu.push(std::make_pair(SIZE, SIZE));

		while (!qu.empty()) {
			std::pair<int, int> front = qu.front();
			qu.pop();

			for (int i = 0; i < 8; i++) {
				int nx = front.first + mov[i][0], ny = front.second + mov[i][1];

				if (!(std::max(0LL, SIZE - cx) <= nx && nx < std::min(2 * SIZE, n - cx + SIZE) && std::max(0LL, SIZE - cy) <= ny && ny < std::min(2 * SIZE, m - cy + SIZE)))
					continue;

				if (visits[nx][ny] != -1)
					continue;

				visits[nx][ny] = visits[front.first][front.second] + 1;
				qu.push(std::make_pair(nx, ny));
			}
		}
		long long result = LLONG_MAX / 2;
		for (int i = std::max(0LL, SIZE - cx); i < std::min(2 * SIZE, n - cx + SIZE); i++) {
			for (int j = std::max(0LL, SIZE - cy); j < std::min(2 * SIZE, m - cy + SIZE); j++) {
				long long nx = i - SIZE + cx, ny = j - SIZE + cy;

				long long gapx = nx - kx, gapy = ny - ky;

				for (int a = 0; a < 8; a++) {
					for (int b = a + 1; b < 8; b++) {
						long long num = mov[a][0] * mov[b][1] - mov[b][0] * mov[a][1];
						if (num == 0)
							continue;

						long long x = gapx * mov[b][1] - gapy * mov[b][0], y = gapx * mov[a][1] * -1 + mov[a][0] * gapy;

						if (x % num != 0 || y % num != 0)
							continue;

						result = std::min(result, aabs(x / num) + aabs(y / num) + visits[i][j]);
					}
				}
			}
		}
		printf("%lld\n", result);
	}
}