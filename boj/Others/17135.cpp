#include <stdio.h>
#include <algorithm>
#include <vector>

int result, n, m, d;
int map[20][20], tmp[20][20];
std::vector<std::pair<int, int>> archers;
std::pair<int, int> enemy_d[3];

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

void solve(int cnt) {
	if (cnt == 3) {
		int t = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				tmp[i][j] = map[i][j];
			}
		}
		
		while (1) {
			for (int i = 0; i < 3; i++)
				enemy_d[i].first = enemy_d[i].second = 0;

			int enemy = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					enemy += map[i][j];

					if (map[i][j] == 1) {
						for (int k = 0; k < archers.size(); k++) {
							int r_d = aabs(archers[k].first - i) + aabs(archers[k].second - j);
							int cur_d = aabs(archers[k].first - enemy_d[k].first) + aabs(archers[k].second - enemy_d[k].second);

							if (r_d > d)
								continue;

							if (r_d < cur_d) {
								enemy_d[k] = std::make_pair(i, j);
							}
							else if (r_d == cur_d) {
								if (j < enemy_d[k].second)
									enemy_d[k] = std::make_pair(i, j);
							}
						}
					}
				}
			}

			if (enemy == 0)
				break;

			for (int i = 0; i < 3; i++) {
				t += map[enemy_d[i].first][enemy_d[i].second];
				map[enemy_d[i].first][enemy_d[i].second] = 0;
			}

			for (int i = n - 1; i >= 1; i--) {
				for (int j = 1; j <= m; j++) {
					map[i + 1][j] = map[i][j];
				}
			}

			for (int i = 1; i <= m; i++)
				map[1][i] = 0;

		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				map[i][j] = tmp[i][j];
			}
		}

		result = std::max(result, t);
		return;
	}

	for (int i = n + 1; i <= n + 1; i++) {
		for (int j = 1; j <= m; j++) {
			bool flag = true;

			for (int k = 0; k < archers.size() && flag; k++)
				if (std::make_pair(i, j) == archers[k])
					flag = false;

			if (flag) {
				archers.push_back({ i, j });
				solve(cnt + 1);
				archers.pop_back();
			}
		}
	}
}
int main(void) {
	scanf("%d %d %d", &n, &m, &d);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &map[i][j]);

	solve(0);
	printf("%d\n", result);
}