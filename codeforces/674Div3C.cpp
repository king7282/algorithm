#include <stdio.h>
#include <algorithm>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		long long n;
		scanf("%I64d", &n);
 
		long long s = 1, e = 100000, r = 1;
 
		while (s <= e) {
			long long mid = (s + e) / 2;
 
			if (mid * mid <= n) {
				s = mid + 1;
				r = std::max(r, mid);
			}
			else
				e = mid - 1;
		}
 
		long long tmp1 = 0, tmp2 = 0;
 
		tmp1 = r - 1 + n / r;
		if (n % r != 0)
			tmp1++;
 
		r++;
		tmp2 = r - 1 + n / r;
		if (n % r != 0)
			tmp2++;
		
		printf("%I64d\n", std::min(tmp1, tmp2) - 1);
	}
}