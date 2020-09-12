#include <stdio.h>
#include <algorithm>
#include <cstring>
 
int check[110];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		memset(check, 0, sizeof(check));
		for (int i = 1; i <= n; i++) {
			int a;
			scanf("%d", &a);
			check[a]++;
		}
 
		int first = 0, second = 0;
		for (int i = 0; i <= 100; i++) {
			if (first == second) {
				if (check[i] >= 2) {
					first++;
					second++;
				}
				else if (check[i] == 1) {
					first++;
				}
				else
					break;
			}
			else {
				if (check[i] >= 1) {
					first++;
				}
				else
					break;
			}
		}
 
		printf("%d\n", first + second);
	}
}