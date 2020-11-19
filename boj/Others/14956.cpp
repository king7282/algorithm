#include <stdio.h>

int map[4][4][2] = { {{0, 0}, {1, 0}, {1, 1}, {0, 1}},{{0, 0}, {0, 1}, {1, 1}, {1, 0}}, {{1, 1}, {0, 1}, {0, 0}, {1, 0}}, {{1, 1}, {1, 0}, {0, 0}, {0, 1}} };
int eexp[16], rx, ry;

void func(int sx, int ex, int sy, int ey, int m, int d) {
	if (sx == ex && sy == ey) {
		rx = sx;
		ry = sy;
		return;
	}

	int gapx = (ex - sx + 1) / 2, gapy = (ey - sy + 1) / 2;

	for (int i = 0; i < 4; i++) {
		if (gapx * gapy * i <= m && m < gapx * gapy * (i + 1)) {
			int next = d;
			if (i == 0) {
				if (d == 0)
					next = 1;
				else if (d == 1)
					next = 0;
				else if (d == 2)
					next = 3;
				else
					next = 2;
			}
			else if (i == 3) {
				if (d == 0)
					next = 3;
				else if (d == 1)
					next = 2;
				else if (d == 2)
					next = 1;
				else
					next = 0;
			}

			func(sx + map[d][i][0] * gapx, ex - (map[d][i][0] + 1) % 2 * gapx, sy + map[d][i][1] * gapy, ey - (map[d][i][1] + 1) % 2 * gapy, m - gapx * gapy * i, next);
			break;
		}
	}

}

int main(void) {
	int k, m, e;
	scanf("%d %d", &k, &m);
	eexp[0] = 1;

	for (int i = 1; i <= 15; i++)
		eexp[i] = eexp[i - 1] * 2;


	func(1, k, 1, k, m - 1, 0);
	printf("%d %d\n", ry, rx);
}