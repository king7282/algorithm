#include <stdio.h>

long long input[10010];

int main(void) {
	while (1) {
		long long n;
		scanf("%lld", &n);

		if (n == 0)
			break;

		long long sum = 0;

		for (int i = 1; i <= n; i++) {
			scanf("%lld", input + i);
			sum += input[i];
		}

		int result = 0;
		for (int i = 1; i <= n; i++) {
			if (sum >= input[i] * n)
				result++;
		}
		printf("%d\n", result);
	}
}