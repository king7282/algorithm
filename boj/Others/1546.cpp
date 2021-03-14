#include <stdio.h>
#include <algorithm>

int input[1010];

int main(void) {
	int n,max1 = 0;
	double result = 0;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		max1 = std::max(max1, input[i]);
	}

	for (int i = 1; i <= n; i++) {
		result += input[i] * 100.0 / max1;
	}

	printf("%.2lf\n", result / n);
}