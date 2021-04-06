#include <stdio.h>

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n, result = 0;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++) {
			int cnt = 0;

			for (int j = 1; j <= i; j++) {
				if (i % j == 0)
					cnt++;
			}

			if (cnt % 2 == 1)
				result++;
		}

		printf("%d\n", result);
	}
}