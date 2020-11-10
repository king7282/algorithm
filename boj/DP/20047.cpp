#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

char tmp[10010], result[10010], in[3];
std::vector<char> input;
int dp[10010][3], n;

int func(int num, int flag) {
	if (num + flag == n) {
		return 1;
	}

	if (dp[num][flag] != -1)
		return dp[num][flag];

	dp[num][flag] = 0;
	if (num < input.size() && input[num] == result[num + flag]) {
		dp[num][flag] = std::max(dp[num][flag], func(num + 1, flag));
	}
	if (flag < 2 && result[num + flag] == in[flag]) {
		dp[num][flag] = std::max(dp[num][flag], func(num, flag + 1));
	}

	return dp[num][flag];
}

int main(void) {
	scanf("%d", &n);
	getchar();

	for (int i = 0; i < n; i++) {
		scanf("%c", tmp + i);
	}
	getchar();

	for (int i = 0; i < n; i++) {
		scanf("%c", result + i);
	}

	int c1, c2;
	scanf("%d %d", &c1, &c2);
	in[0] = tmp[c1];
	in[1] = tmp[c2];

	for (int i = 0; i < n; i++) {
		if (i != c1 && i != c2)
			input.push_back(tmp[i]);
	}


	memset(dp, -1, sizeof(dp));
	if (func(0, 0) == 1)
		printf("YES\n");
	else
		printf("NO\n");
}