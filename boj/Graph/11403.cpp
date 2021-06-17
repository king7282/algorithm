#include <stdio.h>

int matrix[110][110];

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (matrix[i][k] == 1 && matrix[k][j] == 1)
					matrix[i][j] = 1;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}