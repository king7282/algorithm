#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);

	int M = 0, Y = 0;

	for (int i = 1; i <= n; i++) {
		int input;

		scanf("%d", &input);

		Y += (input / 30 + 1) * 10;
		M += (input / 60 + 1) * 15;
	}

	if (Y < M)
		printf("Y %d\n", Y);
	else if (Y > M)
		printf("M %d\n", M);
	else
		printf("Y M %d\n", Y);
}