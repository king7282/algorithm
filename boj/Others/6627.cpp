#include <stdio.h>
#include <algorithm>

int S(int num) {
	int result = 0;

	while (num) {
		result += num % 10;
		num /= 10;
	}

	return result;
}

int main(void) {
	while (1) {
		int n;
		scanf("%d", &n);

		if (n == 0)
			break;

		int result = 100;

		for (int i = 11; i < 100; i++) {
			if (S(n) == S(n * i))
				result = std::min(result, i);
		}

		printf("%d\n", result);
	}
}