#include <stdio.h>
#include <algorithm>

int main(void) {
	long long a, b, c, d, p;

	scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &p);

	printf("%lld\n", std::min(a * p, d * std::max((p - c), 0LL) + b));
}