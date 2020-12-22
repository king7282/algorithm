#include <cstdio>
#include <algorithm>
#include <cstring>

int dp_front[1010], dp_back[1010], input[1010], n;

int solve_front(int num) {
	if (dp_front[num] != -1)
		return dp_front[num];

	dp_front[num] = 1;
	for (int i = num - 1; i >= 1; i--) {
		if(input[num] > input[i])
			dp_front[num] = std::max(dp_front[num], solve_front(i) + 1);
	}

	return dp_front[num];
}

int solve_back(int num) {
	if (dp_back[num] != -1)
		return dp_back[num];

	dp_back[num] = 1;
	for (int i = num + 1; i <= n; i++) {
		if (input[num] > input[i])
			dp_back[num] = std::max(dp_back[num], solve_back(i) + 1);
	}

	return dp_back[num];
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	memset(dp_front, -1, sizeof(dp_front));
	memset(dp_back, -1, sizeof(dp_back));

	int result = 0;
	for (int i = 1; i <= n; i++) {
		result = std::max(result, solve_front(i) + solve_back(i) - 1);
	}

	printf("%d\n", result);
}