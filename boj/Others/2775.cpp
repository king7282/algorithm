#include <stdio.h>

int apartment[15][15];

int main(void) {
	for (int i = 1; i <= 14; i++)
		apartment[0][i] = i;

	for (int i = 1; i <= 14; i++) {
		for (int j = 1; j <= 14; j++) {
			for (int k = 1; k <= j; k++) {
				apartment[i][j] += apartment[i - 1][k];
			}
		}
	}

	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n, k;
		scanf("%d %d", &n, &k);
		printf("%d\n", apartment[n][k]);
	}
}