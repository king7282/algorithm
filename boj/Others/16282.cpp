#include <stdio.h>

int main(void) {
	long long n;
	scanf("%lld", &n);
	int result = 0;

	for (int i = 1; i <= 55; i++) {
		long long tmp = 1;
		for (int j = 1; j <= i + 1; j++)
			tmp *= 2LL;

		if ((tmp - 1) * (i + 1) + i >= n) {
			printf("%d\n", i);
			break;
		}
	}

}