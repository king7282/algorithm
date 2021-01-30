#include <stdio.h>
#include <algorithm>

long double dp[10010], input[10010];

int main(void) {
	int n;
	scanf("%d", &n);
	
	long double result = 0;

	for (int i = 1; i <= n; i++) {
		scanf("%Lf", input + i);

		dp[i] = input[i];
		long double tmp = input[i];
		for (int j = i - 1; j >= 1; j--) {
			dp[i] = std::max(dp[i], dp[j] * tmp);
			tmp *= input[j];
		}

		result = std::max(result, dp[i]);
	}

	printf("%.3Lf\n", result);

}