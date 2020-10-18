#include <stdio.h>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int a, b;
		scanf("%d %d", &a, &b);
 
		printf("%d\n", a ^ b);
	}
}