#include <stdio.h>

int f_p[101], s_p[100];
int price_list[7] = { 0, 5000000, 3000000, 2000000, 500000, 300000, 100000 };

int main(void) {
	int test;
	scanf("%d", &test);
	int cur = 1;
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= i; j++) {
			f_p[cur++] = price_list[i];
		}
	}

	int price = 5120000;
	cur = 1;
	int tmp = 1;
	for (int i = 1; i <= 5; i++) {
		for (int j = 1; j <= tmp; j++) {
			s_p[cur++] = price / tmp;
		}
		tmp *= 2;
	}

	for (int t = 0; t < test; t++) {
		int a, b;
		scanf("%d %d", &a, &b);

		printf("%d\n", f_p[a] + s_p[b]);
	}
}