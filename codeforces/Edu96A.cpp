#include <stdio.h>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		bool flag = false;
		scanf("%d", &n);
		
		for (int i = 0; i <= n && !flag; i++) {
			for (int j = 0; j <= n && !flag; j++) {
				int last = n - i * 3 - j * 5;
				if (last >= 0 && last % 7 == 0) {
					printf("%d %d %d\n", i, j, last / 7);
					flag = true;
				}
			}
		}
 
		if (!flag)
			printf("-1\n");
	}
}
