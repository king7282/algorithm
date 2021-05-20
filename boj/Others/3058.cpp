#include <stdio.h>
#include <algorithm>

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int sum = 0, min1 = 1000000;
		for (int i = 1; i <= 7; i++) {
			int input;
			scanf("%d", &input);
			if (input % 2 == 0) {
				sum += input;
				min1 = std::min(min1, input);
			}
		}
		printf("%d %d\n", sum, min1);
	}
}