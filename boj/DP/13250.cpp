#include <stdio.h>
#include <cstring>

bool check[1000010];
double dp[1000010];
int n;

double func(int num) {
	if (num <= 0)
		return 0;

	if (check[num] == true)
		return dp[num];

	check[num] = true;

	double tmp = 0;
	for (int i = 1; i <= 6; i++)
		tmp += func(num - i);

	tmp /= 6;
	tmp += 1.0;

	return dp[num] = tmp;
}

int main(void) {
	scanf("%d", &n);

	printf("%.9lf\n", func(n));
}