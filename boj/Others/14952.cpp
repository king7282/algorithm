#include <stdio.h>
#include <algorithm>
#define SIZE 4

bool check[43100000];
int goal, r, eexp[18], mov[4][2][2] = { {{1, 0}, {2, 0}}, {{1, 1}, {2, 2}}, {{0, 1}, {0, 2}}, {{1, -1}, {2, -2}} };
int map[4][4];

bool check_map(int bitmask) {
	//printf("%d\n", bitmask);

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			map[i][j] = (bitmask % eexp[i * SIZE + j + 1]) / eexp[i * SIZE + j];
			//printf("%d ", map[i][j]);
		}
		//printf("\n");
	}

	bool flag = false;
	for (int i = 0; i < SIZE && !flag; i++) {
		for (int j = 0; j < SIZE && !flag; j++) {
			if (map[i][j] == 0)
				continue;

			for (int k = 0; k < 4 && !flag; k++) {
				int nx1 = i + mov[k][0][0], ny1 = j + mov[k][0][1], nx2 = i + mov[k][1][0], ny2 = j + mov[k][1][1];
				if (!(0 <= nx1 && nx1 < SIZE && 0 <= ny1 && ny1 < SIZE && 0 <= nx2 && nx2 < SIZE && 0 <= ny2 && ny2 < SIZE))
					continue;

				if (map[i][j] == map[nx1][ny1] && map[i][j] == map[nx2][ny2])
					flag = true;
			}
		}
	}

	//printf("%d\n\n", flag);
	return flag;
}

void func(int turn, int bitmask) {
	if (check[bitmask] == true)
		return;

	check[bitmask] = true;
	if ((bitmask % eexp[goal + 1]) / eexp[goal] != 0) {
		if ((bitmask % eexp[goal + 1]) / eexp[goal] == 2) {
			if (check_map(bitmask))
				r++;
		}
		return;
	}

	if (check_map(bitmask))
		return;

	for (int i = 0; i < SIZE; i++) {
		int next = -1;
		for (int j = 0; j < SIZE; j++) {
			if ((bitmask % eexp[j * SIZE + i + 1]) / eexp[j * SIZE + i] == 0) {
				next = j;
				break;
			}
		}

		if (next != -1) {
			func((turn + 1) % 2, bitmask + eexp[next * SIZE + i] * (turn + 1));
		}
	}
}

int main(void) {
	//freopen("output.txt", "w", stdout);
	int x, fx, fy;
	scanf("%d %d %d", &x, &fx, &fy);

	eexp[0] = 1;
	for (int i = 1; i <= SIZE * SIZE; i++)
		eexp[i] = eexp[i - 1] * 3;

	goal = (fx - 1) * SIZE + fy - 1;
	func(1, eexp[x - 1]);

	printf("%d\n", r);
}