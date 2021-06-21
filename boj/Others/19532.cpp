#include <stdio.h>

int main(void) {
	int a, b, c, d, e, f;
	scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

	printf("%d %d\n", (b * f - e * c) / (b * d - a * e), (c * d - a * f) / (b * d - a * e));
}