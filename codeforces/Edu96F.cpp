#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <climits>

struct info {
	long long x, y, val;
};

info input[2010];
int n;
long long dp[2010][2], k;

long long func(int num, int gap) {
	if (num == n + 1)
		return 0;

	if (dp[num][gap] != -1)
		return dp[num][gap];

	dp[num][gap] = LLONG_MAX / 2;
	
	if ((input[num].y - input[num].x + 1 - gap) * k < input[num].val)
		return dp[num][gap];

	long long cur = 0;
	long long need = input[num].val / k;
	if (input[num].val % k != 0)
		need++;

	if (std::max(0LL, (input[num].y - input[num].x + 1 - gap - 1) * k) < input[num].val) {
		if (input[num + 1].x == input[num].y)
			cur = 1;
		else
			cur = 0;
		dp[num][gap] = std::min(dp[num][gap], func(num + 1, cur) + need * k);
	}
	else {
		dp[num][gap] = std::min(dp[num][gap], func(num + 1, 0) + need * k);
	}

	long long sum = input[num].val, ttmp = num;
	for (int i = num + 1; i <= n; i++) {
		long long remain = (sum / k + 1) * k - sum;

		if (remain == k)
			break;

		if (remain + (input[i].y - input[i].x) * k < input[i].val)
			break;

		sum += input[i].val;

		long long tmp = sum / k;
		if (sum % k != 0)
			tmp++;
		
		if (remain + std::max(0LL, (input[i].y - input[i].x - 1) * k) < input[i].val) {
			if (input[i].y == input[i + 1].x)
				cur = 1;
			else
				cur = 0;

			dp[num][gap] = std::min(dp[num][gap], func(i + 1, cur) + tmp * k);
		}
		else {
			dp[num][gap] = std::min(dp[num][gap], func(i + 1, 0) + tmp * k);
		}

		ttmp = i;
	}

	if (ttmp == n) {
		dp[num][gap] = std::min(dp[num][gap], sum);
	}

	return dp[num][gap];
}

int main(void) {
	scanf("%d %I64d", &n, &k);
	
	for (int i = 1; i <= n; i++) {
		scanf("%I64d %I64d %I64d", &input[i].x, &input[i].y, &input[i].val);
	}
	input[n + 1].x = input[n].y + 1;

	memset(dp, -1, sizeof(dp));
	long long result = func(1, 0);

	if (result >= LLONG_MAX / 2)
		printf("-1\n");
	else
		printf("%I64d\n", result);
}