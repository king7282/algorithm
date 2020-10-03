#include <stdio.h>
#include <algorithm>
#include <climits>
#include <vector>

std::pair<long long, long long> input[100010];
int n;
long long m;

bool OK(long long num) {
	long long result = 0;
	
	for (int i = 1; i <= n; i++) {
		long long tmp = num * input[i].first - input[i].second;
		if (tmp > 0) {
			result += tmp;
			if (result >= m)
				return true;
		}
	}

	if (result >= m)
		return true;
	return false;
}

int main(void) {
	scanf("%d %lld", &n, &m);
	
	for (int i = 1; i <= n; i++)
		scanf("%lld %lld", &input[i].first, &input[i].second);

	long long s = 1, e = INT_MAX, r = INT_MAX;

	while (s <= e) {
		long long mid = (s + e) / 2;

		if (OK(mid)) {
			r = std::min(r, mid);
			e = mid - 1;
		}
		else {
			s = mid + 1;
		}
	}

	printf("%lld\n", r);
}