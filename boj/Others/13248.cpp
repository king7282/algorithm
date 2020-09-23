#include <stdio.h>

int hap[20000010];

int main(void) {
	int a, b, c, d, e;
	scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

	int next = a - 1;
	bool flag = true;
	for (int i = 0; i <= e + c; i++) {
		hap[i] = hap[i - 1] + flag;
		if (i == next) {
			flag ^= 1;
			if (!flag)
				next += b;
			else
				next += a;
		}
	}
	int prev = -1;
	int result = 0, cnt = 0;
	for (int i = d; i <= e; i++) {
		if (hap[i + c - 1] - hap[i - 1] == 0) {
			result++;
		}
		else {
			if (prev == 0) {
				cnt++;
			}
		}
		prev = hap[i + c - 1] - hap[i - 1];
	}

	if (prev == 0)
		cnt++;

	if (e - d == 0) {
		printf("%.9lf\n", (double)result);
	}
	else
		printf("%.9lf\n", (result - cnt) / (double)(e - d));
}