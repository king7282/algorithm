#include <stdio.h>

int first[6], second[6];

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main(void) {
	for (int i = 0; i < 6; i++)
		scanf("%d", first + i);

	for (int i = 0; i < 6; i++)
		scanf("%d", second + i);

	int upper = 0, lower = 6 * 6;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (first[i] > second[j])
				upper++;
		}
	}

	printf("%d/%d\n", upper / gcd(upper, lower), lower / gcd(upper, lower));
}