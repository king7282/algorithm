#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>

bool check1[62501], check2[62501];
std::vector<int> v1[300], v2[300];
std::pair<int, int> input[300];
int dp[251][62501][2];

int func(int num, int value, int flag) {
	if (value < 0)
		return INT_MAX / 2;

	if (num == 0) {
		if (value == 0)
			return 0;
		return INT_MAX / 2;
	}

	if (dp[num][value][flag] != -1)
		return dp[num][value][flag];

	if (flag == 0) {
		dp[num][value][flag] = std::min(func(num - 1, value, flag) + input[num].second, func(num - 1, value - input[num].first, flag));
	}
	else {
		dp[num][value][flag] = std::min(func(num - 1, value, flag) + input[num].first, func(num - 1, value - input[num].second, flag));
	}

	return dp[num][value][flag];
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &input[i].first, &input[i].second);
	}

	v1[1].push_back(0);
	v2[1].push_back(0);
	check1[0] = check2[0] = true;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < v1[i].size(); j++) {
			v1[i + 1].push_back(v1[i][j]);
			if (check1[v1[i][j] + input[i].first] == false)
				v1[i + 1].push_back(v1[i][j] + input[i].first);
			check1[v1[i][j] + input[i].first] = true;
		}

		for (int j = 0; j < v2[i].size(); j++) {
			v2[i + 1].push_back(v2[i][j]);
			if (check2[v2[i][j] + input[i].second] == false)
				v2[i + 1].push_back(v2[i][j] + input[i].second);
			check2[v2[i][j] + input[i].second] = true;
		}
	}

	int result = 62500;
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < v1[n + 1].size(); i++) {
		result = std::min(result, std::max(v1[n + 1][i], func(n, v1[n + 1][i], 0)));
	}

	for (int i = 0; i <= v2[n + 1].size(); i++) {
		result = std::min(result, std::max(v2[n + 1][i], func(n, v2[n + 1][i], 1)));
	}

	printf("%d\n", result);
}