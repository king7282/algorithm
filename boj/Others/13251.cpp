#include <stdio.h>

int input[51];

int main(void) {
	int m, n = 0, k;
	scanf("%d", &m);

	for (int i = 1; i <= m; i++) {
		scanf("%d", input + i);
		n += input[i];
	}

	scanf("%d", &k);

	double result = 0;
	for (int i = 1; i <= m; i++) {
		double tmp = 1;

		for (int j = 1; j <= k; j++) {
			tmp = tmp * (input[i] - j + 1) / (double)(n - j + 1);
		}

		result += tmp;
	}

	printf("%.9lf\n", result);
}