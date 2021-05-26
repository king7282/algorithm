#include <stdio.h>

int main(void) {
	long long n;
	scanf("%lld", &n);

	long long result = 2;

	for (int i = 1; i <= n; i++) {
		result += result - 1;
	}

	printf("%lld\n", result * result);
}