#include <stdio.h>
#include <algorithm>
#include <cstring>
#define MOD 1000000007

int n;
long long dp1[110][110], dp2[110][110], combination[110][110], fac[110];

long long solve_left(int num, int left) {
	if (num == 0) {
		if (left == 0)
			return 1;
		return 0;
	}

	if (left <= 0)
		return 0;

	if (dp1[num][left] != -1)
		return dp1[num][left];

	dp1[num][left] = 0;
	for (int i = num; i >= left; i--) {
		dp1[num][left] = (dp1[num][left] + solve_left(i - 1, left - 1) * combination[num - 1][num - i] % MOD * fac[num - i] % MOD) % MOD;
	}

	return dp1[num][left];
}

long long solve_right(int num, int right) {
	if (num == n + 1) {
		if (right == 0)
			return 1;
		return 0;
	}

	if (right <= 0)
		return 0;

	if (dp2[num][right] != -1)
		return dp2[num][right];

	dp2[num][right] = 0;
	for (int i = num; i <= n - right + 1; i++) {
		dp2[num][right] = (dp2[num][right] + solve_right(i + 1, right - 1) * combination[n - num][i - num] % MOD * fac[i - num] % MOD) % MOD;
	}

	return dp2[num][right];
}

int main(void) {
	int l, r;
	scanf("%d %d %d", &n, &l, &r);
	
	combination[0][0] = 1;

	for (int i = 1; i <= n; i++) {
		combination[i][i] = combination[i][0] = 1;

		for (int j = 1; j < i; j++) {
			combination[i][j] = (combination[i - 1][j] + combination[i - 1][j - 1]) % MOD;
		}
	}

	fac[0] = 1;
	for (long long i = 1; i <= n; i++)
		fac[i] = (fac[i - 1] * i) % MOD;

	long long result = 0;
	memset(dp1, -1, sizeof(dp1));
	memset(dp2, -1, sizeof(dp2));
	
	for (int i = l; i <= n - r + 1; i++) {
		result = (result + combination[n - 1][i - 1] * solve_left(i - 1, l - 1) % MOD * solve_right(i + 1, r - 1) % MOD) % MOD;

	}

	printf("%lld\n", result);
}