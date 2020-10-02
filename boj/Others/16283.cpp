#include <stdio.h>

int main(void) {
	int a, b, n, w;
	scanf("%d %d %d %d", &a, &b, &n, &w);
	int r1, r2, cnt = 0;

	for (int i = 1; i < n; i++) {
		int x = i, y = n - i;
		if (a * x + b * y == w) {
			cnt++;
			r1 = x, r2 = y;
		}
	}

	if (cnt != 1)
		printf("-1\n");
	else
		printf("%d %d\n", r1, r2);
}