#include <stdio.h>
#include <cstring>
#include <vector>

char map[13][7];
int mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
bool visited[13][7];
std::vector<std::pair<int, int>> logs;

void solve(int x, int y) {
	visited[x][y] = true;
	logs.push_back({ x, y });

	for (int i = 0; i < 4; i++) {
		int nx = x + mov[i][0], ny = y + mov[i][1];

		if (!(1 <= nx && nx <= 12 && 1 <= ny && ny <= 6))
			continue;

		if (visited[nx][ny] == true || map[nx][ny] != map[x][y])
			continue;

		solve(nx, ny);
	}

}
int main(void) {

	for (int i = 1; i <= 12; i++)
		for (int j = 1; j <= 6; j++)
			scanf(" %c", &map[i][j]);

	int result = 0;
	while (1) {
		bool finished = true;

		memset(visited, false, sizeof(visited));

		for (int i = 1; i <= 12; i++) {
			for (int j = 1; j <= 6; j++) {
				if (visited[i][j] == false && map[i][j] != '.') {
					logs.clear();
					solve(i, j);

					if (logs.size() >= 4) {
						for (int k = 0; k < logs.size(); k++)
							map[logs[k].first][logs[k].second] = '.';
						finished = false;
					}

				}
			}
		}

		for (int t = 1; t <= 12; t++) {
			for (int i = 11; i >= 1; i--) {
				for (int j = 1; j <= 6; j++) {
					if (map[i][j] != '.' && map[i + 1][j] == '.') {
						std::swap(map[i][j], map[i + 1][j]);
					}
				}
			}
		}

		if (finished)
			break;
		result++;
	}

	
	printf("%d\n", result);
}