#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);

	int prev = 0;
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		printf("%d ", a * i - prev * (i - 1));
		prev = a;
	}
}