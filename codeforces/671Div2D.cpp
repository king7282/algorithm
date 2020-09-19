
#include <stdio.h>
#include <algorithm>
 
int input[100010], result[100010];
 
int main(void) {
	int n;
	scanf("%d", &n);
 
	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
	}
 
	int r = 0;
	std::sort(input + 1, input + 1 + n);
	if (n % 2 == 1) {
		int cur = 1;
		for (int i = n; i >= 1; i--) {
			result[cur] = input[i];
			cur += 2;
 
			if (cur > n)
				cur = 2;
		}
	}
	else {
		int cur = n;
 
		for (int i = 1; i <= n; i += 2)
			result[i] = input[cur--];
 
		result[n] = input[cur--];
 
		for (int i = 2; i < n; i += 2)
			result[i] = input[cur--];
 
	}
 
	for (int i = 2; i < n; i++) {
		if (result[i - 1] > result[i] && result[i] < result[i + 1])
			r++;
	}
 
	printf("%d\n", r);
	for (int i = 1; i <= n; i++)
		printf("%d ", result[i]);
	printf("\n");
}