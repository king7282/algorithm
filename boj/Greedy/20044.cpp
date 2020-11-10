#include <stdio.h>
#include <algorithm>
#include <climits>

int input[10010], n;

int main(void) {
	scanf("%d", &n);
	n *= 2;

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	std::sort(input + 1, input + 1 + n);
	int r = INT_MAX / 2;

	for (int i = 1; i <= n / 2; i++) {
		r = std::min(r, input[i] + input[n - i + 1]);
	}

	printf("%d\n", r);
}