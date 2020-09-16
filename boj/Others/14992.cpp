#include <stdio.h>
#include <vector>

int main(void) {
	long long n, k;
	scanf("%lld %lld", &n, &k);
	if ((1LL << k) - 1LL > n) {
		printf("%lld\n", (1LL << k) - 1);
	}
	else {
		std::vector<long long> bits;
		while (n) {
			bits.push_back(n % 2LL);
			n = n / 2LL;
		}

		long long cur = 0, ttmp = k;
		for (int i = bits.size() - 1; i >= 0; i--) {
			cur = cur * 2LL + bits[i];
			if (bits[i] == 1) {
				k--;
			}

			if (k == 0) {
				cur = cur + 1LL;
				cur = (cur << i);
				break;
			}
		}

		if (k > 0) {
			long long tmp = 1;

			while (k > 0) {
				if ((cur & tmp) == 0) {
					cur += tmp;
					k--;
				}
				tmp = tmp * 2LL;
			}
			printf("%lld\n", cur);
		}
		else {
			long long tmp = cur, cnt = 0;
			while (tmp) {
				if (tmp % 2 == 1)
					cnt++;
				tmp = tmp / 2LL;
			}

			ttmp -= cnt;
			cur += (1LL << (ttmp)) - 1LL;
			printf("%lld\n", cur);
		}
	}
}