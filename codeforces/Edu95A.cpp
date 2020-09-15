#include <stdio.h>
#include <algorithm>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		long long x, y, k;
		scanf("%I64d %I64d %I64d", &x, &y, &k);
		
		long long needX = (k - 1) + y * k;
		long long cur = k + needX / (x - 1);
 
		if (needX % (x - 1) != 0)
			cur++;
 
		printf("%I64d\n", cur);
	}
}