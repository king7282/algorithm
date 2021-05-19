#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);

	int first = 100, second = 100;

	for (int i = 1; i <= n; i++) {
		int a, b;

		scanf("%d %d", &a, &b);

		if (a < b)
			first -= b;
		else if (a > b)
			second -= a;
	}

	printf("%d\n%d\n", first, second);
}