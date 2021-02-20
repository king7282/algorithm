#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>
#include <cassert>

long long dp[110][110], input[110], sum[110], n, m;
bool check[110][110];

long long solve(int num, int group) {
	if (group == m + 1)
		return 0;

	if (num > n)
		return LLONG_MIN / 2;

	if (check[num][group] == true)
		return dp[num][group];
	
	dp[num][group] = LLONG_MIN / 2;

	for (int i = num; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			dp[num][group] = std::max(dp[num][group], solve(j + 2, group + 1) + sum[j] - sum[i - 1]);
		}
	}

	check[num][group] = true;
	return dp[num][group];
} 

int main(void) {
	scanf("%lld %lld", &n, &m);

	for (int i = 1; i <= n; i++) {
		scanf("%lld", input + i);
		sum[i] = sum[i - 1] + input[i];
	}

	memset(check, false, sizeof(check));
	printf("%lld\n", solve(1, 1));
}