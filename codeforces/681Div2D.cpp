#include <stdio.h>
#include <algorithm>
#include <climits>
 
int input[30010];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
 
		for (int i = 1; i <= n; i++)
			scanf("%d", input + i);
 
		int start = n;
		input[n + 1] = INT_MAX / 2;
 
		while (start >= 1) {
			if (input[start] <= input[start + 1])
				start--;
			else
				break;
		}
 
		if (start == 0) {
			printf("YES\n");
			continue;
		}
 
		bool flag = true;
		int minus = 0;
		for (int i = start; i >= 1 && flag; i--) {
			int need = std::max(0, input[i] - input[i + 1]);
 
			input[i] -= std::max(need, minus);
			minus = std::max(minus, need);
 
			if (input[i] < 0)
				flag = false;
		}
 
		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
}