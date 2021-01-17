#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

bool OK[2510][2510];
int dp[2510];

int solve(int num) {
	if (num == -1)
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = solve(num - 1) + 1;

	for (int i = num - 1; i >= 0; i--) {
		if (OK[i][num] == true)
			dp[num] = std::min(dp[num], solve(i - 1) + 1);
	}

	return dp[num];
}

int main(void) {
	std::cin.tie();
	std::ios::sync_with_stdio(false);

	std::string input;
	std::cin >> input;

	for (int i = 0; i < input.size(); i++) {
		OK[i + 1][i] = OK[i][i] = true;
	}

	for (int i = 1; i <= input.size(); i++) {
		for (int j = 0; j < (int)input.size() - i; j++) {
			if (input[j] == input[j + i] && OK[j + 1][j + i - 1] == true)
				OK[j][j + i] = true;
		}
	}

	memset(dp, -1, sizeof(dp));

	printf("%d\n", solve(input.size() - 1));
}