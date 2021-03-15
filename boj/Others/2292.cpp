#include <stdio.h>

int main(void) {
	long long n, cur = 1, result = 1;
	scanf("%lld", &n);

	while (1) {
		if (cur >= n)
			break;
		cur += result * 6;
		result++;
	}

	printf("%lld\n", result);
}