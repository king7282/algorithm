#include <stdio.h>
#include <algorithm>
#include <vector>

int input[110][110];
bool check[110];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &input[i][j]);
		}
	}

	int result = -1, index = -1;
	for (int i = 1; i < n; i++) {
		std::vector<int> gap;

		for (int j = 1; j <= m; j++) {
			gap.push_back(input[j][i] - input[j][n]);
		}

		std::sort(gap.rbegin(), gap.rend());
		int sum = 0, tmp = gap.size();
		for (int j = 0; j < gap.size(); j++) {
			sum += gap[j];
			if (sum < 0) {
				tmp = j;
				break;
			}
		}

		if (result < tmp) {
			result = tmp;
			index = i;
		}
	}

	std::vector<std::pair<int, int>> gap;

	for (int i = 1; i <= m; i++) {
		gap.push_back(std::make_pair(input[i][index] - input[i][n], i));
	}

	std::sort(gap.rbegin(), gap.rend());

	int sum = 0;
	for (int i = 0; i < gap.size(); i++) {
		sum += gap[i].first;
		if (sum < 0) {
			break;
		}
		check[gap[i].second] = true;
	}

	printf("%d\n", m - result);
	for (int i = 1; i <= m; i++) {
		if (check[i] == false)
			printf("%d ", i);
	}

	if (m - result != 0)
		printf("\n");
}