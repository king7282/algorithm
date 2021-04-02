#include <stdio.h>
#include <algorithm>

int main(void) {
	int k, n, m;

	scanf("%d %d %d", &k, &n, &m);

	printf("%d\n", std::max(0, k * n - m));
}