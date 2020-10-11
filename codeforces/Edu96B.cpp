#include <stdio.h>
#include <algorithm>
 
long long input[200010];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, k;
		scanf("%d %d", &n, &k);
 
		for (int i = 1; i <= n; i++) {
			scanf("%I64d", input + i);
		}
 
		std::sort(input + 1, input + 1 + n);
 
		long long result = 0;
		for (int i = n; i >= n - k; i--) {
			result += input[i];
		}
 
		printf("%I64d\n", result);
	}
}