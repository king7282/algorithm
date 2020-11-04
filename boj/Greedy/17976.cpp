#include <stdio.h>
#include <algorithm>
#include <climits>

std::pair<long long, long long> input[100010];
int n;

bool OK(long long num) {
	long long start = input[1].first;
	for (int i = 2; i <= n; i++) {
		if (start + num > input[i].first + input[i].second)
			return false;

		start = std::max(start + num, input[i].first);
	}

	return true;
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld %lld", &input[i].first, &input[i].second);

	std::sort(input + 1, input + 1 + n);

	long long s = 1, e = INT_MAX, r = 1;

	while (s <= e) {
		long long mid = (s + e) / 2;

		if (OK(mid)) {
			r = std::max(r, mid);
			s = mid + 1;
		}
		else
			e = mid - 1;
	}

	printf("%lld\n", r);
}