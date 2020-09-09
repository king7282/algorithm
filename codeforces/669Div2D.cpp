#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
#define SIZE 524288

int dp[300010], input[300010];
std::vector<int> X, height[300010], next[300010];
int tree1[SIZE * 2 + 1], tree2[SIZE * 2 + 1];

void update1(int num, int val) {
	num |= SIZE;
	tree1[num] = val;

	while (num >>= 1) {
		tree1[num] = std::min(tree1[num << 1], tree1[num << 1 | 1]);
	}
}

int query1(int s, int e) {
	s |= SIZE;
	e |= SIZE;

	int r = INT_MAX / 2;
	while (s <= e) {
		if (s % 2 == 1) r = std::min(r, tree1[s]);
		if (e % 2 == 0) r = std::min(r, tree1[e]);
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}

void update2(int num, int val) {
	num |= SIZE;
	tree2[num] = val;

	while (num >>= 1) {
		tree2[num] = std::max(tree2[num << 1], tree2[num << 1 | 1]);
	}
}

int query2(int s, int e) {
	s |= SIZE;
	e |= SIZE;

	int r = -1;
	while (s <= e) {
		if (s % 2 == 1) r = std::max(r, tree2[s]);
		if (e % 2 == 0) r = std::max(r, tree2[e]);
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return r;
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		X.push_back(input[i]);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	for (int i = 1; i <= n; i++) {
		input[i] = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
		next[i].push_back(i + 1);
		height[input[i]].push_back(i);
	}

	memset(tree1, 0x7f, sizeof(tree1));
	memset(tree2, -1, sizeof(tree2));
	for (int i = X.size() - 1; i >= 0; i--) {
		for (int j = height[i].size() - 1; j >= 0; j--) {
			int right = query1(height[i][j], n);

			if (right <= n) {
				next[height[i][j]].push_back(right);
			}

			update1(height[i][j], height[i][j]);
		}

		for (int j = 0; j < height[i].size(); j++) {
			int left = query2(1, height[i][j]);

			if (left >= 1) {
				next[left].push_back(height[i][j]);
			}

			update2(height[i][j], height[i][j]);
		}
	}

	memset(tree1, 0x7f, sizeof(tree1));
	memset(tree2, -1, sizeof(tree2));
	for (int i = 0; i < X.size(); i++) {
		for (int j = height[i].size() - 1; j >= 0; j--) {
			int right = query1(height[i][j], n);

			if (right <= n) {
				next[height[i][j]].push_back(right);
			}

			update1(height[i][j], height[i][j]);
		}

		for (int j = 0; j < height[i].size(); j++) {
			int left = query2(1, height[i][j]);

			if (left >= 1) {
				next[left].push_back(height[i][j]);
			}
			update2(height[i][j], height[i][j]);
		}
	}

	dp[n] = 0;
	for (int i = n - 1; i >= 1; i--) {
		dp[i] = INT_MAX / 2;
		for (int j = 0; j < next[i].size(); j++) {
			dp[i] = std::min(dp[i], dp[next[i][j]] + 1);
		}
	}

	printf("%d\n", dp[1]);
}