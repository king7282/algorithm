#include <stdio.h>

int numbers[6] = { 1, 1, 2, 2, 2, 8 };

int main(void) {
	for (int i = 0; i < 6; i++) {
		int input;
		scanf("%d", &input);

		printf("%d ", numbers[i] - input);
	}
}