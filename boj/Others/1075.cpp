#include <stdio.h>

int main(void) {
	int n, f;
	scanf("%d %d", &n, &f);

	n /= 100;

	for (int i = 0; i <= 99; i++) {
		if ((n * 100 + i) % f == 0) {
			printf("%02d\n", i);
			break;
		}
	}
}