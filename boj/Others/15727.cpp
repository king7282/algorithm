#include <stdio.h>

int main(void) {
	int t;
	scanf("%d", &t);

	if (t % 5 == 0)
		printf("%d\n", t / 5);
	else
		printf("%d\n", t / 5 + 1);
}