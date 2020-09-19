#include <stdio.h>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		getchar();
 
		bool flag1 = false, flag2 = false;
		for (int i = 1; i <= n; i++) {
			char c;
			scanf("%c", &c);
			c -= '0';
 
			if (i % 2 == 1) {
				if (c % 2 == 1) {
					flag1 = true;
				}
			}
			else {
				if (c % 2 == 0)
					flag2 = true;
			}
		}
 
		if (n % 2 == 1) {
			if (flag1) {
				printf("1\n");
			}
			else
				printf("2\n");
		}
		else {
			if (flag2) {
				printf("2\n");
			}
			else
				printf("1\n");
		}
	}
}