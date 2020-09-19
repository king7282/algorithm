#include <stdio.h>
#include <algorithm>
 
int input[1010];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, x;
		scanf("%d %d", &n, &x);
 
		bool flag = false;
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", input + i);
			sum += input[i] - x;
			if (input[i] == x)
				flag = true;
		}
 
		std::sort(input + 1, input + 1 + n);
		if (input[1] == input[n] && input[1] == x) {
			printf("0\n");
		}
		else {
			if (sum == 0 || flag) {
				printf("1\n");
			}
			else
				printf("2\n");
		}
	}
}