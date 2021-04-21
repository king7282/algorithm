#include <stdio.h>
#include <algorithm>

int main(void) {
	int t = 1;
	while (1) {
		int l, p, v;

		scanf("%d %d %d", &l, &p, &v);

		if (l == 0 && p == 0 && v == 0)
			break;

		int result = v / p * l;

		result += std::min(l, v % p);

		printf("Case %d: %d\n", t++, result);
	}
}