#include <stdio.h>

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 1; t <= test; t++) {
		int y = 0, k = 0;

		for (int i = 1; i <= 9; i++) {
			int a, b;
			scanf("%d %d", &a, &b);

			y += a;
			k += b;
		}

		if (y < k)
			printf("Korea\n");
		else if (y > k)
			printf("Yonsei\n");
		else
			printf("Draw\n");
	}
}