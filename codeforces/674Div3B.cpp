#include <stdio.h>
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, m;
		scanf("%d %d", &n, &m);
 
		bool flag = false;
 
		for (int i = 1; i <= n; i++) {
			int a, b, c, d;
			scanf("%d %d %d %d", &a, &b, &c, &d);
 
			if (b == c)
				flag = true;
		}
 
		if (m % 2 == 0 && flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
}