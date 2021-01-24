#include <stdio.h>
#include <vector>
#include <algorithm>

int input[100010];

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	int result = 1, cnt = 1;

	for (int i = 2; i <= n; i++) {
		if (input[i] >= input[i - 1])
			cnt++;
		else
			cnt = 1;

		result = std::max(result, cnt);
	}

	cnt = 1;
	for (int i = 2; i <= n; i++) {
		if (input[i] <= input[i - 1])
			cnt++;
		else
			cnt = 1;

		result = std::max(result, cnt);
	}

	printf("%d\n", result);
}