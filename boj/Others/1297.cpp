#include <stdio.h>
#include <cmath>

int main(void) {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	double x = (double)a / sqrt(b * b + c * c);

	int height = x * b, width = x * c;

	printf("%d %d\n", height, width);

}