#include <stdio.h>

int main(void) {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	printf("%d\n", (a + 1) * (b + 1) / (c + 1) - 1);
}