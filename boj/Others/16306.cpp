#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

std::vector<long long> v;

int main(void) {
	long long x;
	scanf("%lld", &x);

	for (long long i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			v.push_back(i);
			if (i != x / i)
				v.push_back(x / i);
		}
	}

	long long result = LLONG_MAX / 2;
	for (int i = 0; i < v.size(); i++) {
		long long next = x / v[i], a = v[i];

		for (long long j = 1; j * j <= next; j++) {
			if (next % j == 0) {
				long long b = j, c = next / j;

				result = std::min(result, 2 * (a * b + b * c + c * a));
			}
		}
	}

	printf("%lld\n", result);
}