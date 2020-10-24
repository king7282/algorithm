#include <stdio.h>
 
bool check[100001];
 
int main(void) {
	for (int i = 2; i * i <= 100000; i++) {
		if (check[i] == false) {
			for (int j = i * i; j <= 100000; j += i)
				check[j] = true;
		}
	}
 
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
 
		int left = 1;
		for (int i = n - 1; i <= 100000; i++) {
			if (check[i] == false && check[i - (n - 1)] == true) {
				left = i;
				break;
			}
		}
 
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j)
					printf("%d ", left - (n - 1));
				else
					printf("1 ");
			}
			printf("\n");
		}
	}
}