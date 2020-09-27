#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);

	if (n % 2 == 1) {
		printf("Bob\n");
	}
	else {
		printf("Alice\n1\n");
	}
}