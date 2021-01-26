#include <stdio.h>
#include <algorithm>
#include <climits>

long long input[2010][2010], result[2010][2010], rsum[2010][2010];

long long sum(int x, int y) {
	if (x < 0 || y < 0)
		return 0;
	return rsum[x][y];
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%lld", &input[i][j]);
			input[i][j] *= -1;
		}
	}

	if (m == 1) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				printf("%lld ", input[i][j]);
			}
			printf("\n");
		}

		return 0;
	}
	
	for (int i = 1 + m / 2; i <= n - m / 2; i++) {
		for (int j = 1 + m / 2; j <= n - m / 2; j++) {
			int rx = i - m / 2, ry = j - m / 2;
			rsum[i][j] = rsum[i - 1][j] + rsum[i][j - 1] - rsum[i - 1][j - 1];
			result[i][j] = input[rx][ry] - (sum(i, j) - sum(i - m, j) - sum(i, j - m) + sum(i - m, j - m));
			rsum[i][j] += result[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%lld ", result[i][j]);
		}
		printf("\n");
	}

}