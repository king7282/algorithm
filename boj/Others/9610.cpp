#include <stdio.h>

char p[5][5] = { "Q1", "Q2", "Q3", "Q4", "AXIS" };
int result[5];

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (x == 0 || y == 0)
			result[4]++;
		else if (x > 0 && y > 0)
			result[0]++;
		else if (x > 0 && y < 0)
			result[3]++;
		else if (x < 0 && y > 0)
			result[1]++;
		else
			result[2]++;
	}

	for (int i = 0; i < 5; i++) {
		printf("%s: %d\n", p[i], result[i]);
	}
}