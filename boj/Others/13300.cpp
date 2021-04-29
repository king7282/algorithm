#include <stdio.h>
#include <algorithm>

int students[2][7];

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		students[a][b]++;
	}

	int result = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= 6; j++) {
			result += students[i][j] / k;

			if (students[i][j] % k != 0)
				result++;
		}
	}

	printf("%d\n", result);
}