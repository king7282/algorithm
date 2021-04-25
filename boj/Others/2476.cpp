#include <stdio.h>
#include <algorithm>

int input[4];

int main(void) {
	int test, result = 0;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		
		scanf("%d %d %d", input, input + 1, input + 2);

		std::sort(input, input + 3);

		if (input[0] == input[2]) {
			result = std::max(result, input[0] * 1000 + 10000);
		}
		else if (input[0] == input[1] || input[1] == input[2]) {
			result = std::max(result, 1000 + input[1] * 100);
		}
		else {
			result = std::max(result, 100 * input[2]);
		}
	}

	printf("%d\n", result);
}
