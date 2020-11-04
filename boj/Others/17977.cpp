#include <stdio.h>

int arr[1000010] = { 0, 0, 0, 0, 1, 2, 2, };

int main(void) {
	int n;
	scanf("%d", &n);

	if (n <= 6)
		printf("%d\n", arr[n]);
	else {
		int pp = 1, p = 2, index = 7, cur = 3;
		while (index <= n) {
			for (int i = 0; i < pp * 2 && index <= n; i++, index++) {
				arr[index] = cur;
			}

			int tmp = pp;
			pp = p;
			p = tmp * 2;
			cur++;
		}

		printf("%d\n", arr[n]);
	}
}