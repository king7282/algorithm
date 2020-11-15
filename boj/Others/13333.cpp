#include <stdio.h>
#include <algorithm>

int input[1010];

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	int result = 0;
	for (int q = 0; q <= 10000; q++) {
		int lower = 0, upper = 0;
		for (int i = 1; i <= n; i++) {
			if (input[i] >= q)
				upper++;
			if (input[i] < q)
				lower++;
		}

		if (upper >= q && lower <= q) {
			result = std::max(result, q);
		}
	}
	printf("%d\n", result);
}