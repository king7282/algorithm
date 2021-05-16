#include <stdio.h>

int main(void) {
	int test;

	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int v, e;

		scanf("%d %d", &v, &e);

		printf("%d\n", 2 - v + e);
	}
}