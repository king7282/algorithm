#include <stdio.h>
#include <algorithm>
#include <climits>

int input[100010];

int main(void) {
	int n, x;
	scanf("%d %d", &n, &x);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);
	
	if (n == 1) {
		printf("1\n");
		return 0;
	}

	input[0] = INT_MIN / 2;

	std::sort(input + 1, input + 1 + n);
	int result = 0;
	for (int i = 1; i <= n; i++) {
		if (input[i] + input[i - 1] > x)
			break;

		result++;
	}

	printf("%d\n", result);
}