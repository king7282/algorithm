#include <stdio.h>

int remain[4] = { 25, 10, 5, 1 };

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int a;
		scanf("%d", &a);

		for (int i = 0; i < 4; i++) {
			printf("%d ", a / remain[i]);
			a %= remain[i];
		}
		printf("\n");
	}
}