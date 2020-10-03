#include <stdio.h>
#include <math.h>

int main(void) {
	int a, b, c, d;
	scanf("%d %d %d %d", &a, &b, &c, &d);

	double s = (a + b + c + d) / 2.0;

	double result = sqrt((s - a) * (s - b) * (s - c) * (s - d));
	printf("%lf\n", result);
}