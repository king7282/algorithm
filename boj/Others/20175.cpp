#include <stdio.h>
#include <algorithm>
#include <vector>

int main(void) {
	long long n, gap;
	scanf("%lld %lld", &n, &gap);

	std::vector<long long> value1, value2;
	for (long long i = 0; i < n; i++) {
		long long a;
		scanf("%lld", &a);

		value1.push_back((a - i * gap) * 10);
		value2.push_back((a + i * gap) * 10);
	}

	std::sort(value1.begin(), value1.end());
	std::sort(value2.begin(), value2.end());
	long long mid1 = (value1.front() + value1.back()) / 2, mid2 = (value2.front() + value2.back()) / 2;
	long long result = std::min(mid1 - value1.front(), mid2 - value2.front());

	printf("%lld.%lld\n", result / 10, result % 10);
}