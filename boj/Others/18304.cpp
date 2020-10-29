#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

bool check[11][11];
char map[11][11];
int dp[1 << 20], number[11][11], mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
std::vector<std::pair<int, int>> points;
int n;

void dfs(int x, int y, int cnt) {
	number[x][y] = cnt;

	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];
		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n)) {
			continue;
		}
		
		if (map[nx][ny] != '*' || number[nx][ny] != 30)
			continue;

		dfs(nx, ny, cnt);
	}
}

int OK(int x, int y) {
	int flag = -1;
	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];
		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n)) {
			continue;
		}

		if (map[nx][ny] == '*')
			flag = number[nx][ny];
	}
	return flag;
}

void make_points(int x, int y) {
	check[x][y] = true;
	points.push_back(std::make_pair(x, y));

	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];
		if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n)) {
			continue;
		}

		if (check[nx][ny] == true)
			continue;

		if (map[nx][ny] == '.' && OK(nx, ny) == OK(x, y)) {
			make_points(nx, ny);
		}
	}
}

int func(int bitmask) {
	if (dp[bitmask] != -1)
		return dp[bitmask];

	dp[bitmask] = 0;
	bool ok[22] = { false, };

	for (int i = 0; i < points.size(); i++) {
		if ((bitmask & (1 << i)) != 0)
			continue;

		bool flag = true;
		for (int j = 0; j < points.size() && flag; j++) {
			if ((bitmask & (1 << j)) == 0)
				continue;

			for (int k = 0; k < 4 && flag; k++) {
				int nx = points[j].first + mov[k][0], ny = points[j].second + mov[k][1];
				if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n)) {
					continue;
				}

				if (std::make_pair(nx, ny) == points[i])
					flag = false;
			}
		}

		if (flag) {
			ok[func(bitmask | (1 << i))] = true;
		}
	}

	for (int i = 0; i <= points.size() + 1; i++) {
		if (ok[i] == false) {
			dp[bitmask] = i;
			break;
		}
	}

	return dp[bitmask];
}

int main(void) {
	scanf("%d", &n);
	getchar();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%c", &map[i][j]);
			number[i][j] = 30;
		}
		getchar();
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == '*' && number[i][j] == 30) {
				dfs(i, j, cnt++);
			}
		}
	}

	long long result = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (check[i][j] == false && map[i][j] == '.' && OK(i, j) != -1) {
				points.clear();
				make_points(i, j);
				memset(dp, -1, sizeof(dp));
				result = (result ^ func(0));
				
			}
		}
	}

	if (result == 0)
		printf("Second player will win\n");
	else
		printf("First player will win\n");

}