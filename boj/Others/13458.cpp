#include <stdio.h>

long long input[1000010];

int main(void) {
	long long n, b, c;
	scanf("%lld", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld", input + i);
	scanf("%lld %lld", &b, &c);

	long long result = 0;
	for (int i = 1; i <= n; i++) {
		result++;
		input[i] -= b;

		if (input[i] > 0) {
			result += input[i] / c;
			if (input[i] % c != 0)
				result++;
		}
	}

	printf("%lld\n", result);
}