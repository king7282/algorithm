#include <stdio.h>
#define MOD 1000

long long matrix[10][10], result[10][10];
int n;

void power(long long p) {
	if (p == 1) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				result[i][j] = matrix[i][j] % MOD;
			}
		}
		return;
	}

	power(p / 2);

	long long tmp[10][10];
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			tmp[i][j] = 0;
			for (int k = 1; k <= n; k++) {
				tmp[i][j] = (tmp[i][j] + result[i][k] * result[k][j] % MOD) % MOD;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			result[i][j] = tmp[i][j];
		}
	}
	if (p % 2 == 1) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				tmp[i][j] = 0;
				for (int k = 1; k <= n; k++) {
					tmp[i][j] = (tmp[i][j] + result[i][k] * matrix[k][j] % MOD) % MOD;
				}
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				result[i][j] = tmp[i][j];
		}
	}
}

int main(void) {
	long long b;

	scanf("%d %lld", &n, &b);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%lld", &matrix[i][j]);
			
		}
	}
	power(b);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%lld ", result[i][j]);
		}
		printf("\n");
	}
}