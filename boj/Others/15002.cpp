#include <stdio.h>
#include <cmath>
#define M_PI       3.14159265358979323846

int main(void) {
	int n;
	double a, b;
	scanf("%d %lf %lf", &n, &a, &b);
	int ax, ay;
	scanf("%d %d", &ax, &ay);

	bool flag = true;
	for (int i = 0; i < n; i++) {
		int x, y, dist;
		scanf("%d %d", &x, &y);

		dist = (x - ax) * (x - ax) + (y - ay) * (y - ay);

		if (dist >= a * a && dist <= b * b) {
			flag = false;
			double radian = 0;
			if (x == ax) {
				radian = M_PI / 2;
				if (ay > y) {
					radian *= -1;
				}
			}
			else {
				radian = atan((double)(ay - y) / (ax - x));
				if (x < ax) {
					if (y > ay)
						radian += M_PI;
					else
						radian -= M_PI;
				}
			}
			printf("%d %d %lf %lf\n", x, y, sqrt(dist), radian);
			break;
		}
	}

	if (flag)
		printf("impossible\n");
}