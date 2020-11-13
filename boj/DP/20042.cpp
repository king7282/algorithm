#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>

std::vector<long long> X[3010];
long long input[3001], dp[3000][9001];
int n;

long long func(int num, int index) {
	if (num == n)
		return X[n][index] * X[n][index];

	if (dp[num][index] != -1)
		return dp[num][index];

	dp[num][index] = LLONG_MIN / 2;
	int next = std::upper_bound(X[num + 1].begin(), X[num + 1].end(), input[num + 1] - input[num] - X[num][index]) - X[num + 1].begin();
	if(next > 0)
		dp[num][index] = std::max(dp[num][index], func(num + 1, next - 1) + X[num][index] * X[num][index]);
	if(index > 0)
		dp[num][index] = std::max(dp[num][index], func(num, index - 1));

	if (dp[num][index] < 0)
		dp[num][index] = LLONG_MIN / 2;

	return dp[num][index];
}

int main(void) {
	scanf("%d", &n);
	input[n + 1] = LLONG_MAX / 2;

	for (int i = 1; i <= n; i++) {
		scanf("%lld", input + i);
	}

	input[0] = LLONG_MIN / 2;
	for (int i = 1; i <= n; i++) {
		long long cur = std::min(input[i] - input[i - 1], input[i + 1] - input[i]);
		X[i].push_back(cur);
		for (int j = i - 1; j >= 1; j--) {
			cur = std::min(input[j] - input[j - 1], input[j + 1] - input[j] - cur);
			X[j].push_back(cur);
		}

		cur = std::min(input[i] - input[i - 1], input[i + 1] - input[i]);
		for (int j = i + 1; j <= n; j++) {
			cur = std::min(input[j + 1] - input[j], input[j] - input[j - 1] - cur);
			X[j].push_back(cur);
		}
	}

	for (int i = 1; i <= n; i++) {
		X[i].push_back(0);
		std::sort(X[i].begin(), X[i].end());
		X[i].erase(std::unique(X[i].begin(), X[i].end()), X[i].end());
	}

	memset(dp, -1, sizeof(dp));
	if (func(1, X[1].size() - 1) < 0)
		while (1);
	printf("%lld\n", func(1, X[1].size() - 1));
}