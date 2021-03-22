#include <stdio.h>

int main(void) {
	int a, b, v;

	scanf("%d %d %d", &a, &b, &v);

	int result = (v - a) / (a - b);
	if ((v - a) % (a - b) != 0)
		result++;

	printf("%d\n", result + 1);
}