#include <stdio.h>

int main(void) {
	int n;
	scanf("%d", &n);

	long long result = 0;

	for (int i = n; i >= 0; i--) {
		for (int j = i; j >= 0; j--) {
			result += i + j;
		}
	}

	printf("%lld\n", result);
}