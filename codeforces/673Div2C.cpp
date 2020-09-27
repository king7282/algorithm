#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
 
int input[300010], result[300010];
std::vector<int> X, diff[300010];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		X.clear();
 
		diff[0].clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d", input + i);
			X.push_back(input[i]);
			diff[i].clear();
			result[i] = INT_MAX / 2;
		}
 
		std::sort(X.begin(), X.end());
		X.erase(std::unique(X.begin(), X.end()), X.end());
 
		for (int i = 1; i <= n; i++) {
			int index = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
			diff[index].push_back(i);
		}
 
		for (int i = 0; i < X.size(); i++) {
			if (diff[i].size() == 0)
				continue;
 
			int gap = std::max(diff[i][0], n - diff[i].back() + 1);
			for (int j = 1; j < diff[i].size(); j++) {
				gap = std::max(gap, diff[i][j] - diff[i][j - 1]);
			}
 
			result[gap] = std::min(result[gap], X[i]);
		}
 
		int prev = INT_MAX / 2;
		for (int i = 1; i <= n; i++) {
			prev = std::min(prev, result[i]);
			if (prev == INT_MAX / 2)
				printf("-1 ");
			else
				printf("%d ", prev);
		}
		printf("\n");
 
	}
 }