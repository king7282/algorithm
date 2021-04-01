#include <stdio.h>
#include <algorithm>
#include <vector>

bool win[100010];

int main(void) {
	int n, a, b;
	scanf("%d %d %d", &n, &a, &b);

	win[a] = win[b] = true;

	std::vector<int> v[2];
	int index = 1, result = 0;

	for (int i = 1; i <= n; i++)
		v[index].push_back(i);

	while (v[index % 2].size() > 1) {
		v[(index + 1) % 2].clear();
		for (int i = 0; i < (int)v[index % 2].size() - 1; i += 2) {
			if (win[v[index % 2][i]] == true && win[v[index % 2][i + 1]] == true) {
				result = index;
				v[(index + 1) % 2].push_back(v[index % 2][i]);
			}
			else if (win[v[index % 2][i]] == true) {
				v[(index + 1) % 2].push_back(v[index % 2][i]);
			}
			else {
				v[(index + 1) % 2].push_back(v[index % 2][i + 1]);
			}
		}

		if (v[index % 2].size() % 2 == 1)
			v[(index + 1) % 2].push_back(v[index % 2].back());
		index++;
	}
	printf("%d\n", result);
}