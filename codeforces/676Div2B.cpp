#include <stdio.h>
#include <queue>
#include <algorithm>
#include <cstring>
 
bool check[210][210];
char map[210][210];
int n, mov[4][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
 
bool func(void) {
	std::queue<std::pair<int, int>> qu;
	memset(check, false, sizeof(check));
 
	check[1][1] = true;
	qu.push(std::make_pair(1, 1));
	map[1][1] = map[n][n] = '0';
	while (!qu.empty()) {
		std::pair<int, int> front = qu.front();
		qu.pop();
 
		for (int i = 0; i < 4; i++) {
			int nx = front.first + mov[i][0], ny = front.second + mov[i][1];
 
			if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
				continue;
 
			if (map[nx][ny] != '0' || check[nx][ny] == true)
				continue;
 
			check[nx][ny] = true;
			qu.push(std::make_pair(nx, ny));
		}
	}
 
	if (check[n][n] == true)
		return true;
 
	memset(check, false, sizeof(check));
 
	check[1][1] = true;
	qu.push(std::make_pair(1, 1));
	map[1][1] = map[n][n] = '1';
	while (!qu.empty()) {
		std::pair<int, int> front = qu.front();
		qu.pop();
 
		for (int i = 0; i < 4; i++) {
			int nx = front.first + mov[i][0], ny = front.second + mov[i][1];
 
			if (!(1 <= nx && nx <= n && 1 <= ny && ny <= n))
				continue;
 
			if (map[nx][ny] != '1' || check[nx][ny] == true)
				continue;
 
			check[nx][ny] = true;
			qu.push(std::make_pair(nx, ny));
		}
	}
	
	if (check[n][n] == true)
		return true;
	return false;
}
 
int main(void) {
	int test;
	scanf("%d", &test);
	
	for (int t = 1; t <= test; t++) {
		scanf("%d", &n);
		getchar();
 
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%c", &map[i][j]);
			}
			getchar();
		}
 
		if (func() == false) {
			printf("0\n");
			continue;
		}
 
		bool flag = true;
		std::pair<int, int> tmp[4] = { {1, 2}, {2, 1}, {n, n - 1}, {n - 1, n} };
		for (int i = 0; i < 4 && flag; i++) {
			if (map[tmp[i].first][tmp[i].second] == '0')
				map[tmp[i].first][tmp[i].second] = '1';
			else
				map[tmp[i].first][tmp[i].second] = '0';
 
			if (func() == false) {
				printf("1\n%d %d\n", tmp[i].first, tmp[i].second);
				flag = false;
			}
 
			for (int j = i + 1; j < 4 && flag; j++) {
				if (map[tmp[j].first][tmp[j].second] == '0')
					map[tmp[j].first][tmp[j].second] = '1';
				else
					map[tmp[j].first][tmp[j].second] = '0';
 
				if (func() == false) {
					printf("2\n%d %d\n%d %d\n", tmp[i].first, tmp[i].second, tmp[j].first, tmp[j].second);
					flag = false;
				}
				if (map[tmp[j].first][tmp[j].second] == '0')
					map[tmp[j].first][tmp[j].second] = '1';
				else
					map[tmp[j].first][tmp[j].second] = '0';
			}
			if (map[tmp[i].first][tmp[i].second] == '0')
				map[tmp[i].first][tmp[i].second] = '1';
			else
				map[tmp[i].first][tmp[i].second] = '0';
		}
 
		if (flag)
			while (1);
	}
}