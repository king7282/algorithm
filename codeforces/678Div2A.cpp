#include <stdio.h>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, m;
		scanf("%d %d", &n, &m);
		int sum = 0;
 
		for (int i = 1; i <= n; i++) {
			int a;
			scanf("%d", &a);
			sum += a;
		}
 
		if (sum == m)
			printf("YES\n");
		else
			printf("NO\n");
	}
}