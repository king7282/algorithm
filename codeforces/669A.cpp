#include <stdio.h>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, one = 0, zero = 0;
		scanf("%d", &n);
 
		for (int i = 1; i <= n; i++) {
			int tmp;
			scanf("%d", &tmp);
			if (tmp == 0)
				zero++;
			else
				one++;
		}
 
		if (zero >= one) {
			printf("%d\n", zero);
			for (int i = 0; i < zero; i++)
				printf("0 ");
			printf("\n");
		}
		else {
			if (one % 2 == 1) {
				printf("%d\n", one - 1);
				for (int i = 0; i < one - 1; i++)
					printf("1 ");
			}
			else {
				printf("%d\n", one);
				for (int i = 0; i < one; i++) {
					printf("1 ");
				}
			}
			printf("\n");
		}
	}
}