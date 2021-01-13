#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>

std::vector<std::pair<int, int>> input;
std::vector<int> graph[100010];
int indegree[100010];
bool check[100010];

bool dfs(int num, int p) {
	check[num] = true;

	for (int i = 0; i < graph[num].size(); i++) {
		if (graph[num][i] == p)
			continue;

		if (check[graph[num][i]] == true)
			return false;

		if (!dfs(graph[num][i], num))
			return false;
	}

	return true;
}

int main(void) {
	int cnt = 0;
	while (1) {
		cnt++;
		std::vector<int> X;
		bool flag = false;

		while (1) {
			int a, b;
			scanf("%d %d", &a, &b);
			
			if (a == -1 && b == -1) {
				flag = true;
				break;
			}
			if (a == 0 && b == 0) {
				break;
			}

			input.push_back(std::make_pair(a, b));
			X.push_back(a);
			X.push_back(b);
		}

		if (flag)
			break;

		std::sort(X.begin(), X.end());
		X.erase(std::unique(X.begin(), X.end()), X.end());
		int n = X.size();

		for (int i = 0; i < input.size(); i++) {
			input[i].first = std::lower_bound(X.begin(), X.end(), input[i].first) - X.begin();
			input[i].second = std::lower_bound(X.begin(), X.end(), input[i].second) - X.begin();
			graph[input[i].first].push_back(input[i].second);
			indegree[input[i].second]++;
		}
		X.clear();
		input.clear();
		
		bool result = true;
		int root = -1;
		for (int i = 0; i < n && result; i++) {
			if (indegree[i] == 0) {
				if (root != -1)
					result = false;
				root = i;
			}
		}

		if (result && !dfs(root, -1)) 
			result = false;

		for (int i = 0; i < n && result; i++) {
			if (check[i] == false)
				result = false;
		}

		if (result) {
			printf("Case %d is a tree.\n", cnt);
		}
		else
			printf("Case %d is not a tree.\n", cnt);


		for (int i = 0; i < n; i++) {
			graph[i].clear();
			indegree[i] = 0;
			check[i] = false;
		}

	}
}