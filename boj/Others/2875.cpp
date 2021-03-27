#include <stdio.h>
#include <algorithm>

int main(void) {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	int result = 0;
	for (int i = 0; i <= std::min(k, n); i++) {
		int woman = n - i, man = m - (k - i);

		if (man < 0)
			continue;

		result = std::max(result, std::min(woman / 2, man));
	}

	printf("%d\n", result);
}