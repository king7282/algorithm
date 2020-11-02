#include <stdio.h>
#include <algorithm>
 
int n;
long long a[200010], b[200010];
 
bool OK(long long num) {
	long long sum = 0;
 
	for (int i = 1; i <= n; i++) {
		if (a[i] > num)
			sum += b[i];
	}
 
	if (sum <= num)
		return true;
	return false;
}
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		scanf("%d", &n);
 
		for (int i = 1; i <= n; i++)
			scanf("%I64d", a + i);
 
		long long sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%I64d", b + i);
			sum += b[i];
		}
 
		long long s = 1, e = sum, r = sum;
 
		while (s <= e) {
			long long mid = (s + e) / 2;
			if (OK(mid)) {
				e = mid - 1;
				r = std::min(r, mid);
			}
			else
				s = mid + 1;
		}
 
		printf("%I64d\n", r);
	}
}