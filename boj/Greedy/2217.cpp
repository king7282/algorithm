#include <stdio.h>
#include <algorithm>
#include <climits>

long long input[100010], n;

bool OK(long long num) {
	for (int i = n; i >= 1; i--) {
		long long weight = num / (n - i + 1);
		if (num % (n - i + 1) != 0)
			weight++;

		if (input[i] >= weight)
			return true;
	}

	return false;
}

int main(void) {
	scanf("%lld", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld", input + i);

	std::sort(input + 1, input + 1 + n);
	long long s = 0, e = LLONG_MAX / 3, r = 0;

	while (s <= e) {
		long long mid = (s + e) / 2;

		if (OK(mid)) {
			s = mid + 1;
			r = std::max(r, mid);
		}
		else
			e = mid - 1;
	}

	printf("%lld\n", r);
}