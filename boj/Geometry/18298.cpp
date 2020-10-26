#include <stdio.h>

struct points {
	long long x, y;
};

long long ccw(points a, points b, points c) {
	return a.x * b.y + b.x * c.y + c.x * a.y - b.x * a.y - c.x * b.y - a.x * c.y;
}

long long aabs(long long num) {
	if (num < 0)
		return num * -1;
	return num;
}

points input[52];

int main(void) {
	long long result = 0;
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		long long tmp = 0;
		for (int i = 1; i <= n; i++)
			scanf("%lld %lld", &input[i].x, &input[i].y);

		points a;
		a.x = a.y = -1;

		for (int i = 2; i <= n; i++) {
			tmp += ccw(a, input[i - 1], input[i]);
		}

		tmp += ccw(a, input[n], input[1]);

		result += aabs(tmp);
	}
	printf("%lld\n", result / 2);
}