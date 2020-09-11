#include <stdio.h>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

int input[301][301], check[301];
int tree[301];

int find(int num) {
	if (tree[num] == -1)
		return num;
	return tree[num] = find(tree[num]);
}

int main(void) {
	while (1) {
		int n;
		scanf("%d", &n);

		if (n == 0)
			break;

		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				scanf("%d", &input[i][j]);
				input[j][i] = input[i][j];
			}
		}

		std::vector<std::pair<int, int>> edge;
		int result = INT_MAX / 2;
		for (int i = 1; i <= n; i++) {
			check[i] = 1;

			for (int j = 1; j <= n; j++) {
				if (i == j)
					continue;

				if (check[i] * input[i][j] > 0)
					check[j] = -1;
				else
					check[j] = 1;
			}

			edge.clear();
			int sum = 0, cnt = 0;
			for (int a = 1; a <= n; a++) {
				for (int b = a + 1; b <= n; b++) {
					if (input[a][b] * check[a] * check[b] > 0) {
						cnt++;
						sum += input[a][b] * check[a] * check[b];
						edge.push_back(std::make_pair(a, b));
					}
				}
			}

			if (cnt <= 2 * n - 2) {
				for (int j = 1; j <= n; j++) {
					if (i == j) continue;
					
					bool flag = true;
					int tmp_sum = sum;
					int tmp_cnt = cnt;
					memset(tree, -1, sizeof(tree));
					check[j] *= -1;
					for (int a = 1; a <= n; a++) {
						if (a == j)
							continue;

						if (input[j][a] * check[j] * check[a] > 0) {
							tmp_sum += input[j][a] * check[j] * check[a];
							tmp_cnt++;
							if (find(j) == find(a)) {
								flag = false;
								break;
							}
							tree[find(j)] = find(a);
						}
						else {
							tmp_sum += input[j][a] * check[j] * check[a];
							tmp_cnt--;
						}
					}

					if (flag && tmp_cnt == n - 1) {
						for (int a = 0; a < edge.size() && flag; a++) {
							if (input[edge[a].first][edge[a].second] * check[edge[a].first] * check[edge[a].second] < 0)
								continue;
							if (find(edge[a].first) == find(edge[a].second))
								flag = false;
							else
								tree[find(edge[a].first)] = find(edge[a].second);
						}

						if (flag)
							result = std::min(result, tmp_sum);
					}

					check[j] *= -1;
				}
			}
		}

		if (result == INT_MAX / 2)
			result = -1;
		printf("%d\n", result);
	}
}