#include <stdio.h>
#include <algorithm>

int main(void) {
	long long n, l;
	scanf("%lld %lld", &n, &l);

	long long start = 0, length = 101;
	
	for (int i = l - 1; i <= 100; i++) {
		if (i * (i + 1) / 2 == n) {
			if (length > i + 1) {
				length = i + 1;
				start = 0;
			}
		}
	}

	for (int i = l; i <= 100; i++) {
		long long s = 0, e = 1000000000, r = 1000000000;

		while (s <= e) {
			long long mid = (s + e) / 2;

			if ((mid + i) * (mid + 1 + i) / 2 - mid * (mid + 1) / 2 >= n) {
				e = mid - 1;
				r = std::min(r, mid);
			}
			else
				s = mid + 1;
		}

		if ((r + i) * (r + 1 + i) / 2 - r * (r + 1) / 2 == n) {
			if (length > i) {
				length = i;
				start = r + 1;
			}
		}

	}


	if (length > 100) {
		printf("-1\n");
	}
	else {
		for (int i = 0; i < length; i++) {
			printf("%lld ", start + i);
		}
	}
}