#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <climits>

int dp[1010];
std::string input;

int func(int num) {
	if (num == input.size())
		return 0;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = func(num + 1) + input[num] - '0';
	int prev = 2;

	for (int i = num; i < input.size(); i++) {
		int tmp = prev - 1 + (10 - input[i] + '0');
		dp[num] = std::min(dp[num], func(i + 1) + tmp);
		prev = tmp;
	}
	return dp[num];
}
int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();


	std::cin >> input;
	memset(dp, -1, sizeof(dp));

	std::cout << func(0);
	
}