#include <stdio.h>
#include <algorithm>
#include <cstring>

int a[1010];
bool check[1010];

int main(void) {
	int n;
	scanf("%d", &n);
	a[0] = a[1] = 1;

	for (int i = 2; i <= n; i++) {
		memset(check, false, sizeof(check));
		int k = 1;
		while (i - 2 * k >= 0) {
			int value = a[i - k] * 2 - a[i - 2 * k];
			if (value > 0)
				check[value] = true;

			k++;
		}

		for (int j = 1; j <= 1000; j++) {
			if (check[j] == false) {
				a[i] = j;
				break;
			}
		}
	}
	printf("%d\n", a[n]);
}