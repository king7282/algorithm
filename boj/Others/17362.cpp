#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);

	if (n <= 5)
		printf("%d\n", n);
	else {
		n -= 6;
		if ((n / 4) % 2 == 0) {
			printf("%d\n", 4 - n % 4);
		}
		else {
			printf("%d\n", n % 4 + 2);
		}
	}
}