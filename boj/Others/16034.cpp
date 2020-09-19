#include <stdio.h>
#include <algorithm>

int main(void) {
	while (1) {
		long long n;
		scanf("%lld", &n);

		if (n == 0)
			break;

		long long result = 1, start = n;
		for (long long i = 2; i <= std::min(n, 50000LL); i++) {
			long long s = 1, e = n, r = 1;

			while (s <= e) {
				long long mid = (s + e) / 2;

				if (i * mid + i * (i - 1) / 2 <= n) {
					r = std::max(r, mid);
					s = mid + 1;
				}
				else {
					e = mid - 1;
				}
			}

			if (r * i + i * (i - 1) / 2 == n) {
				result = i;
				start = r;
			}
		}


		printf("%lld %lld\n", start, result);
	}
}