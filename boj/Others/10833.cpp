#include <stdio.h>

int main(void) {
	int n, result = 0;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		result += b % a;
	}

	printf("%d\n", result);
}