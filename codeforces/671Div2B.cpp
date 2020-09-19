#include <stdio.h>
#include <algorithm>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		long long x;
		scanf("%I64d", &x);
		
		long long cur = 1, r = 0;
 
		while (1) {
			x -= cur * (cur + 1) / 2;
			if (x < 0)
				break;
			r++;
			cur = cur * 2 + 1;
		}
 
		printf("%I64d\n", r);
	}
}