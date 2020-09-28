#include <stdio.h>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, x;
		scanf("%d %d", &n, &x);
 
		int limits = 2, floor = 1;
 
		for (int i = 1; i <= n; i++) {
			if (i > limits) {
				floor++;
				limits += x;
			}
		}
		printf("%d\n", floor);
	}
}