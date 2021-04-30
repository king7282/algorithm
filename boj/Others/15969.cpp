#include <stdio.h>
#include <algorithm>

int main(void) {
	int n;
	scanf("%d", &n);

	int max1 = 0, min1 = 1001;

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		max1 = std::max(max1, a);
		min1 = std::min(min1, a);
	}

	printf("%d\n", max1 - min1);
}