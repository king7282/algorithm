#include <stdio.h>
#include <algorithm>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		long long a[3];
		scanf("%I64d %I64d %I64d", a, a + 1, a + 2);
 
		std::sort(a, a + 3);
 
		long long mid = a[0] + a[1] - 1;
		long long result;
		if (mid > a[2]) {
			result = mid - a[2] + 1;
		}
		else {
			result = a[2] - mid + 1;
		}
		printf("%I64d\n", result);
	}
}