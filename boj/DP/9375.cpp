#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>

long long dp[32], input[32];
int n, iindex;
std::map<std::string, int> map;

long long solve(int num) {
	if (num == iindex)
		return 1;

	if (dp[num] != -1)
		return dp[num];

	dp[num] = 0;
	for (int i = num + 1; i <= iindex; i++) {
		if (num == 0 && i == iindex)
			break;
		dp[num] += solve(i);
	}

	dp[num] *= input[num];
	return dp[num];
}

int main(void) {
	int test;
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> test;

	for (int t = 0; t < test; t++) {
		std::cin >> n;
		map.clear();

		for (int i = 0; i < n; i++) {
			std::string tmp1, tmp2;
			std::cin >> tmp1 >> tmp2;

			if (map.find(tmp2) == map.end())
				map[tmp2] = 0;

			map[tmp2]++;
		}

		iindex = 1;
		for (auto it = map.begin(); it != map.end(); it++) {
			input[iindex++] = it->second;
		}

		input[0] = 1;

		memset(dp, -1, sizeof(dp));
		printf("%lld\n", solve(0));
	}
}