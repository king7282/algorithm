#include <stdio.h>

int main(void) {
	long long n;
	scanf("%lld", &n);

	long long result = 0, tmp = 1, cnt = 1;


	while (n >= tmp * 10) {
		long long next = tmp * 10;

		result += (next - tmp) * cnt;
		cnt++;
		tmp = next;

	}
	result += (n - tmp + 1) * cnt;
	printf("%lld\n", result);
}