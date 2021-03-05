#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

std::vector<int> graph[10010];
int p_value[10010], dp[10010][2][2];
bool check[10010][2][2];

int solve(int num, int p, int num_flag, int p_flag) {
	if (check[num][num_flag][p_flag] != false)
		return dp[num][num_flag][p_flag];

	check[num][num_flag][p_flag] = true;
	int &r = dp[num][num_flag][p_flag];
	r = 0;
	int gap = INT_MIN / 2;

	for (int i = 0; i < graph[num].size(); i++) {
		if (graph[num][i] == p)
			continue;

		if (num_flag == 1) {
			r += solve(graph[num][i], num, 0, 1);
		}
		else {
			r += std::max(solve(graph[num][i], num, 1, 0) + p_value[graph[num][i]], solve(graph[num][i], num, 0, 0));
			gap = std::max(gap, solve(graph[num][i], num, 1, 0) + p_value[graph[num][i]] - solve(graph[num][i], num, 0, 0));
		}
	}

	if (num_flag == 0 && p_flag == 0 && gap < 0) {
		r += gap;
	}

	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", p_value + i);

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	printf("%d\n", std::max(solve(1, 0, 0, 0), solve(1, 0, 1, 0) + p_value[1]));

}