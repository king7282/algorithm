#include <stdio.h>

int main(void) {
	int n, cnt = 0, cur;
	scanf("%d", &n);

	for (cur = 1; cur <= n; cur++) {
		cnt += cur;
		if (cnt >= n)
			break;
	}

	int upper, lower;
	if (cur % 2 == 0) {
		upper = 1, lower = cur;
		n -= (cnt - cur);
		while (--n) {
			upper++;
			lower--;
		}
	}
	else {
		upper = cur, lower = 1;
		n -= (cnt - cur);
		while (--n) {
			upper--;
			lower++;
		}
	}
	printf("%d/%d\n", upper, lower);
}