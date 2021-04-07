#include <stdio.h>

int input[110];

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	for (int i = 2; i <= n; i++) {
		int g = gcd(input[1], input[i]);
		printf("%d/%d\n", input[1] / g, input[i] / g);
	}
}