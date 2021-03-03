#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <climits>

bool check[22];
std::pair<long long, long long> dp[22];
char input[22];

std::pair<long long, long long> solve(int num) {
	if (num <= 0)
		return std::make_pair(0, 0);

	if (num == 1)
		return std::make_pair(input[num] - '0', input[num] - '0');

	if (check[num] == true)
		return dp[num];

	check[num] = true;
	dp[num] = std::make_pair(LLONG_MAX / 2, LLONG_MIN / 2);

	if (input[num - 1] == '+') {
		dp[num].first = std::min(dp[num].first, solve(num - 2).first + (long long)input[num] - '0');
		dp[num].second = std::max(dp[num].second, solve(num - 2).second + (long long)input[num] - '0');

		if (input[num - 3] == '+') {
			dp[num].first = std::min(dp[num].first, solve(num - 4).first + ((long long)input[num - 2] - '0' + (long long)input[num] - '0'));
			dp[num].second = std::max(dp[num].second, solve(num - 4).second + ((long long)input[num - 2] - '0' + (long long)input[num] - '0'));
		}
		else if (input[num - 3] == '-') {
			dp[num].first = std::min(dp[num].first, solve(num - 4).first - ((long long)input[num - 2] - '0' + (long long)input[num] - '0'));
			dp[num].second = std::max(dp[num].second, solve(num - 4).second - ((long long)input[num - 2] - '0' + (long long)input[num] - '0'));
		}
		else {
			dp[num].first = std::min(dp[num].first, solve(num - 4).second * ((long long)input[num - 2] - '0' + (long long)input[num] - '0'));
			dp[num].first = std::min(dp[num].first, solve(num - 4).first * ((long long)input[num - 2] - '0' + (long long)input[num] - '0'));

			dp[num].second = std::max(dp[num].second, solve(num - 4).second * ((long long)input[num - 2] - '0' + (long long)input[num] - '0'));
			dp[num].second = std::max(dp[num].second, solve(num - 4).first * ((long long)input[num - 2] - '0' + (long long)input[num] - '0'));
		}
	}
	else if (input[num - 1] == '-') {
		dp[num].first = std::min(dp[num].first, solve(num - 2).first - ((long long)input[num] - '0'));
		dp[num].second = std::max(dp[num].second, solve(num - 2).second - ((long long)input[num] - '0'));

		if (input[num - 3] == '+') {
			dp[num].first = std::min(dp[num].first, solve(num - 4).first + ((long long)input[num - 2] - '0' - ((long long)input[num] - '0')));
			dp[num].second = std::max(dp[num].second, solve(num - 4).second + ((long long)input[num - 2] - '0' - ((long long)input[num] - '0')));
		}
		else if (input[num - 3] == '-') {
			dp[num].first = std::min(dp[num].first, solve(num - 4).first - ((long long)input[num - 2] - '0' - ((long long)input[num] - '0')));
			dp[num].second = std::max(dp[num].second, solve(num - 4).second - ((long long)input[num - 2] - '0' - ((long long)input[num] - '0')));
		}
		else {
			dp[num].first = std::min(dp[num].first, solve(num - 4).second * ((long long)input[num - 2] - '0' - ((long long)input[num] - '0')));
			dp[num].first = std::min(dp[num].first, solve(num - 4).first * ((long long)input[num - 2] - '0' - ((long long)input[num] - '0')));

			dp[num].second = std::max(dp[num].second, solve(num - 4).second * ((long long)input[num - 2] - '0' - ((long long)input[num] - '0')));
			dp[num].second = std::max(dp[num].second, solve(num - 4).first * ((long long)input[num - 2] - '0' - ((long long)input[num] - '0')));
		}
	}
	else {
		dp[num].first = std::min(dp[num].first, solve(num - 2).first * ((long long)input[num] - '0'));
		dp[num].first = std::min(dp[num].first, solve(num - 2).second * ((long long)input[num] - '0'));

		dp[num].second = std::max(dp[num].second, solve(num - 2).first * ((long long)input[num] - '0'));
		dp[num].second = std::max(dp[num].second, solve(num - 2).second * ((long long)input[num] - '0'));

		if (input[num - 3] == '+') {
			dp[num].first = std::min(dp[num].first, solve(num - 4).first + (((long long)input[num - 2] - '0') * ((long long)input[num] - '0')));
			dp[num].second = std::max(dp[num].second, solve(num - 4).second + (((long long)input[num - 2] - '0') * ((long long)input[num] - '0')));
		}
		else if (input[num - 3] == '-') {
			dp[num].first = std::min(dp[num].first, solve(num - 4).first - (((long long)input[num - 2] - '0') * ((long long)input[num] - '0')));
			dp[num].second = std::max(dp[num].second, solve(num - 4).second - (((long long)input[num - 2] - '0') * ((long long)input[num] - '0')));
		}
		else {
			dp[num].first = std::min(dp[num].first, solve(num - 4).second * (((long long)input[num - 2] - '0') * ((long long)input[num] - '0')));
			dp[num].first = std::min(dp[num].first, solve(num - 4).first * (((long long)input[num - 2] - '0') * ((long long)input[num] - '0')));

			dp[num].second = std::max(dp[num].second, solve(num - 4).second * (((long long)input[num - 2] - '0') * ((long long)input[num] - '0')));
			dp[num].second = std::max(dp[num].second, solve(num - 4).first * (((long long)input[num - 2] - '0') * ((long long)input[num] - '0')));
		}
	}

	return dp[num];
}

int main(void) {
	int n;
	scanf("%d", &n);

	input[0] = '+';
	for (int i = 1; i <= n; i++) {
		scanf(" %c", input + i);
	}

	memset(dp, -1, sizeof(dp));
	printf("%lld\n", solve(n).second);
}