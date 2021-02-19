#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <climits>

int dp[100010][5][5], n = 0;
std::vector<int> foots;
int weights[5][5] = { {2, 2, 2, 2, 2}, {0, 1, 3, 4, 3}, {0, 3, 1, 3, 4}, {0, 4, 3, 1, 3}, {0, 3, 4, 3, 1} };

int solve(int num, int left, int right) {
	if (left != 0 && right != 0 && left == right)
		return INT_MAX / 2;

	if (num == n)
		return 0;

	if (dp[num][left][right] != -1)
		return dp[num][left][right];

	dp[num][left][right] = std::min(solve(num + 1, foots[num], right) + weights[left][foots[num]], solve(num + 1, left, foots[num]) + weights[right][foots[num]]);
	
	return dp[num][left][right];
}

int main(void) {
	while (1) {
		int input;
		scanf("%d", &input);
		if (input == 0)
			break;

		n++;
		foots.push_back(input);
	}

	memset(dp, -1, sizeof(dp));
	printf("%d\n", solve(0, 0, 0));
}