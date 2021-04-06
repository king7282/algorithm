#include <stdio.h>
#include <algorithm>
#define MOD 1000000

struct info {
	long long up1, up2, do1, do2;
	info(long long up1 = 1,long long up2 = 1, long long do1 = 1,long long do2 = 0) : up1(up1), up2(up2), do1(do1), do2(do2) {}
};


info power(long long p) {
	if (p == 1)
		return info();

	info tmp = power(p / 2);
	info result;

	result.up1 = (tmp.up1 * tmp.up1 + tmp.up2 * tmp.do1) % MOD;
	result.up2 = (tmp.up1 * tmp.up2 + tmp.up2 * tmp.do2) % MOD;
	result.do1 = (tmp.do1 * tmp.up1 + tmp.do2 * tmp.do1) % MOD;
	result.do2 = (tmp.do1 * tmp.up2 + tmp.do2 * tmp.do2) % MOD;

	if (p % 2 == 1) {
		tmp = result;
		result.up1 = (tmp.up1 + tmp.up2) % MOD;
		result.up2 = tmp.up1;
		result.do1 = (tmp.do1 + tmp.do2) % MOD;
		result.do2 = tmp.do1;
	}

	return result;
}

int main(void) {
	long long n;
	scanf("%lld", &n);

	if (n <= 1)
		printf("%lld\n", n);
	else {
		info result = power(n - 1);
		printf("%lld\n", result.up1);
	}
}