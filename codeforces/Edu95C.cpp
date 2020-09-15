#include <stdio.h>
#include <algorithm>
#include <cstring>
 
int dp[200010][2]; // 0 is friend, 1 is me
int input[200010], n;
 
int func(int num, int type) {
	if (num > n)
		return 0;
 
	if (dp[num][type] != -1)
		return dp[num][type];
 
	if (type == 0) {
		dp[num][type] = std::min(func(num + 1, 1) + input[num], func(num + 2, 1) + input[num] + input[num + 1]);
	}
	else {
		dp[num][type] = std::min(func(num + 1, 0), func(num + 2, 0));
	}
 
	return dp[num][type];
}
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", input + i);
 
		memset(dp, -1, sizeof(dp));
		printf("%d\n", func(1, 0));
	}
}