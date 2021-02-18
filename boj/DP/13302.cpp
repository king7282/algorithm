#include <stdio.h>
#include <algorithm>
#include <cstring>

bool check[110];
int dp[110][110], n;

int solve(int num, int coupon) {
	if (num > n)
		return 0;

	if (dp[num][coupon] != -1)
		return dp[num][coupon];

	int &r = dp[num][coupon];

	if (check[num] == true)
		r = solve(num + 1, coupon);
	else {
		r = std::min(solve(num + 1, coupon) + 10000, solve(num + 3, coupon + 1) + 25000);
		r = std::min(r, solve(num + 5, coupon + 2) + 37000);

		if (coupon >= 3) {
			r = std::min(r, solve(num + 1, coupon - 3));
		}
	}

	return r;
}

int main(void) {
	int m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		int a;
		scanf("%d", &a);

		check[a] = true;
	}
	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(1, 0));
}