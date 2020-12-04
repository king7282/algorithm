#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>

bool check[800010];
int input[5010];
std::vector<std::pair<int, int>> v[400010];

int main(void) {
	int w, n, min1 = INT_MAX / 2, max1 = 0;
	scanf("%d %d", &w, &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		for (int j = 1; j < i; j++) {
			min1 = std::min(min1, input[i] + input[j]);
			max1 = std::max(max1, input[i] + input[j]);
			if (v[input[i] + input[j]].size() < 2)
				v[input[i] + input[j]].push_back(std::make_pair(j, i));
		}
	}

	bool flag = false;
	for (int i = 1; i <= n && !flag; i++) {
		for (int j = 1; j < i && !flag; j++) {
			int left = w - input[i] - input[j];
			if (left < min1 || left > max1 || check[left] == true || v[left].size() == 0)
				continue;
			check[left] = true;

			for (int z = 0; z < 2 && z < v[left].size(); z++) {
				if (v[left][z].first != j && v[left][z].second != i && v[left][z].first != i && v[left][z].second != j) {
					flag = true;
					break;
				}
			}
		}
	}

	if (flag)
		printf("YES\n");
	else
		printf("NO\n");
}