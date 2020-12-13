#include <stdio.h>
#include <algorithm>
#include <cmath>

long long n;
long long arr1[300010], arr2[300010];

long long aabs(long long num) {
	if (num < 0)
		return -1 * num;
	return num;

}
long long OK(long long num) {
	long long r = 0;

	for (int i = 1; i <= n; i++) {
		r += aabs(arr1[i] - (num + aabs(n / 2 + 1 - i)));
		r += aabs(arr2[i] - (num + aabs(n / 2 + 1 - i)));
	}

	return r;
}

long long para(long long s, long long e) {
	while (s <= e) {
		long long mid = (s + e) / 2;
		long long tmp1 = OK(mid - 1), tmp2 = OK(mid), tmp3 = OK(mid + 1);
		if (tmp1 >= tmp2 && tmp2 <= tmp3)
			return mid;
		else if (tmp1 < tmp2 && tmp2 < tmp3)
			e = mid - 1;
		else
			s = mid + 1;
	}
	return -1;
}

int main(void) {
	scanf("%lld", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld", arr1 + i);

	for (int i = 1; i <= n; i++)
		scanf("%lld", arr2 + i);

	long long result = para(1LL, 1000000000000LL);
	if (result == -1) {
		printf("%lld\n", std::min(OK(0), OK(1000000000000)));
	}
	else
		printf("%lld\n", OK(result));
}