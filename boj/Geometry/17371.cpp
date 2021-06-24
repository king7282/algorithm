#include <stdio.h>
#include <algorithm>
#include <climits>

std::pair<int, int> input[1010];

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &input[i].first, &input[i].second);
	}

	int result = INT_MAX / 2, index = 1;

	for (int i = 1; i <= n; i++) {
		int longest = 0;
		for (int j = 1; j <= n; j++) {
			if (i == j)
				continue;
			longest = std::max(longest, (input[i].first - input[j].first) * (input[i].first - input[j].first) + (input[i].second - input[j].second) * (input[i].second - input[j].second));
		}

		if (longest < result) {
			result = longest;
			index = i;
		}
	}

	printf("%d %d\n", input[index].first, input[index].second);
}