#include <stdio.h>
#include <algorithm>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		printf("2\n");
		if (n == 2) {
			printf("1 2\n");
			continue;
		}
 
		if (n == 3) {
			printf("1 3\n");
			printf("2 2\n");
			continue;
		}
 
		printf("%d %d\n", n, n - 2);
		printf("%d %d\n", n - 1, n - 1);
 
		int cur = n - 1;
 
		while (cur > 2) {
			printf("%d %d\n", cur, cur - 2);
			cur--;
		}
	}
}
