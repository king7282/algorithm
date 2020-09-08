#include <stdio.h>
#include <algorithm>
#include <cstring>
 
int input[1010], result[1010];
bool check[1010];
 
int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 1; t <= test; t++) {
		int n;
		scanf("%d", &n);
 
		for (int i = 1; i <= n; i++)
			scanf("%d", input + i);
		
		memset(check, false, sizeof(check));
 
		std::sort(input + 1, input + 1 + n);
		result[1] = input[n];
		check[n] = true;
 
		int cur = result[1];
 
		for (int i = 2; i <= n; i++) {
			int max1 = 0, index = 0;
 
			for (int j = 1; j <= n; j++) {
				if (check[j])
					continue;
 
				if (gcd(cur, input[j]) > max1) {
					max1 = gcd(cur, input[j]);
					index = j;
				}
			}
 
			check[index] = true;
			result[i] = input[index];
			cur = max1;
		}
 
		for (int i = 1; i <= n; i++)
			printf("%d ", result[i]);
		printf("\n");
	} 
}