#include <stdio.h>
#include <algorithm>
#include <climits>

char input[100010];
long long sum[200010];

int main(void) {
	int n, A = 0, B = 0, C = 0;
	scanf("%d", &n);
	getchar();
	
	for (int i = 1; i <= n; i++) {
		scanf("%c", input + i);
		if (input[i] == 'A') {
			A++;
			sum[i] = sum[i - 1] + 1;
		}
		else if (input[i] == 'B') {
			B++;
			sum[i] = sum[i - 1] + 1000000LL;
		}
		else {
			C++;
			sum[i] = sum[i - 1] + 1000000000000LL;
		}
	}

	for (int i = n + 1; i <= 2 * n; i++) {
		if (input[i - n] == 'A') {
			sum[i] = sum[i - 1] + 1;
		}
		else if (input[i - n] == 'B') {
			sum[i] = sum[i - 1] + 1000000LL;
		}
		else {
			sum[i] = sum[i - 1] + 1000000000000LL;
		}
	}

	long long result = LLONG_MAX / 2;
	for (int i = 1; i <= n; i++) {
		long long a = sum[i + A - 1] - sum[i - 1], b = sum[i + A + B - 1] - sum[i + A - 1], c = sum[i + A + B + C - 1] - sum[i + A + B - 1];

		a %= 1000000LL;
		b %= 1000000000000L;
		b /= 1000000LL;
		c /= 1000000000000LL;

		result = std::min(result, A - a + B - b + C - c);

		c = sum[i + A + C - 1] - sum[i + A - 1], b = sum[i + A + B + C - 1] - sum[i + A + C - 1];
		b %= 1000000000000L;
		b /= 1000000LL;
		c /= 1000000000000LL;

		result = std::min(result, A - a + B - b + C - c);
	}
	printf("%lld\n", result);
}