#include <stdio.h>
#include <cstring>
#include <algorithm>

int input[1000010], dp[1000010][4];

int func(int num, int p) {
	if (num == 1000000)
		return 0;

	if (dp[num][p] != -1)
		return dp[num][p];

	dp[num][p] = func(num + 1, p);
	if (input[num] == 1) {
		if (p != 1)
			dp[num][p] = std::max(dp[num][p], func(num + 1, 1) + 1);
	}
	else if (input[num] == 2) {
		if (p != 2)
			dp[num][p] = std::max(dp[num][p], func(num + 1, 2) + 1);
	}
	else if (input[num] == 3) {
		dp[num][p] = std::max(dp[num][p], func(num + 1, 3) + 1);
	}

	return dp[num][p];
}

int main(void) {
	int k;
	scanf("%d", &k);

	for (int i = 0; i < k; i++) {
		int a;
		scanf("%d", &a);
		input[a]++;
	}

	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int a;
		scanf("%d", &a);
		input[a] += 2;
	}

	memset(dp, -1, sizeof(dp));
	printf("%d\n", func(0, 0));
}