#include <stdio.h>
#include <algorithm>
 
int input[1010];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, k;
		scanf("%d %d", &n, &k);
 
		for (int i = 1; i <= n; i++) {
			scanf("%d", input + i);
		}
 
		std::sort(input + 1, input + 1 + n);
		long long result = 0;
		for (int i = 2; i <= n; i++) {
			result += (long long)(k - input[i]) / input[1];
		}
 
		printf("%I64d\n", result);
	}
}