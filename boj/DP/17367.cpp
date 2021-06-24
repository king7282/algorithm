#include <stdio.h>
#include <cstring>
#include <algorithm>

double dp[1010][7][7][7];
bool check[1010][7][7][7];

double solve(int x, int d1, int d2, int d3) {
	if (x < 0)
		return 0;

	if (check[x][d1][d2][d3] == true)
		return dp[x][d1][d2][d3];

	check[x][d1][d2][d3] = true;
	double &r = dp[x][d1][d2][d3];

	if (d1 == d2 && d2 == d3) {
		r = 10000 + 1000 * d1;
	}
	else if (d1 == d2 || d1 == d3) {
		r = 1000 + 100 * d1;
	}
	else if (d2 == d3) {
		r = 1000 + 100 * d2;
	}
	else {
		r = 100 * std::max({ d1, d2, d3 });
	}

	double tmp = 0;
	for (int i = 1; i <= 6; i++) {
		tmp += solve(x - 1, i, d1, d2);
	}

	r = std::max(r, tmp / 6.0);

	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);

	double result = 0;
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			for (int k = 1; k <= 6; k++) {
				result += solve(n - 3, i, j, k);
			}
		}
	}

	printf("%.6lf\n", result / (6 * 6 * 6.0));
}