#include <stdio.h>
#include <algorithm>

long long diff[100010];

int main(void) {
	int n;
	scanf("%d", &n);

	int prev;
	long long value = 0;
	scanf("%d", &prev);
	diff[1] = prev;
	for (int i = 2; i <= n; i++) {
		int a;
		scanf("%d", &a);
		diff[i] = prev - a;
		if (diff[i] > 0)
			value += diff[i];
		prev = a;
	}

	value += prev;
	if (value > 0) {
		printf("%I64d\n", value / 2 + value % 2);
	}
	else {
		printf("%I64d\n", (-value) / 2 * -1);
	}
	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		int a, b;
		long long c;
		scanf("%d %d %I64d", &a, &b, &c);

		if (a > 1) {
			if (diff[a] > 0) {
				value -= diff[a];
			}
			diff[a] -= c;
			if (diff[a] > 0) {
				value += diff[a];
			}
		}
		else {
			diff[a] -= c;
		}

		if (b < n) {
			if (diff[b + 1] > 0) {
				value -= diff[b + 1];
			}
			diff[b + 1] += c;
			if (diff[b + 1] > 0) {
				value += diff[b + 1];
			}
		}
		else {
			value += c;
		}

		if (value > 0) {
			printf("%I64d\n", value / 2 + value % 2);
		}
		else {
			printf("%I64d\n", (-1 * value) / 2 * -1);
		}
	}

}