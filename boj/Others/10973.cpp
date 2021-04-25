#include <stdio.h>
#include <algorithm>

int input[10010];

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", input + i);

	if (std::prev_permutation(input, input + n)) {
		for (int i = 0; i < n; i++)
			printf("%d ", input[i]);
		printf("\n");
	}
	else
		printf("-1\n");
}