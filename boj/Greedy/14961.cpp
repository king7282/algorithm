#include <stdio.h>
#include <algorithm>

int main(void) {
	int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
	int n;
	scanf("%d", &n);

	int curx = 0, cury = 0, d = 1;
	for (int i = 1; i <= n; i++) {
		int a, b, r = 0;
		scanf("%d %d", &a, &b);

		if (d == 0) {
			r = xmax - curx + 1;
			curx = xmax + 1;
			xmax = curx;
		}
		else if (d == 1) {
			r = ymax - cury + 1;
			cury = ymax + 1;
			ymax = cury;
		}
		else if (d == 2) {
			r = curx - xmin + 1;
			curx = xmin - 1;
			xmin = curx;
		}
		else {
			r = cury - ymin + 1;
			cury = ymin - 1;
			ymin = cury;
		}
		printf("%d ", r);
		d = (d + b + 4) % 4;
	}
	printf("\n");
}