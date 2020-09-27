#include <stdio.h>
#include <vector>
#include <algorithm>

int input[100010], cnt[100010], index;
std::vector<int> graph[100010];

std::pair<int, int> func(int num) {
	std::pair<int, int> result = std::make_pair(-1, 0);

	for (int i = 0; i < graph[num].size(); i++) {
		std::pair<int, int> tmp = func(graph[num][i]);
		if (tmp.first > result.first) {
			result = tmp;
		}
	}

	if (result.first == -1) {
		result.first = 1;
		result.second = ++index;
	}
	else
		result.first++;

	cnt[result.second] = std::max(cnt[result.second], result.first);
	return result;
}

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= k; i++) {
		scanf("%d", input + i);
	}

	std::sort(input + 1, input + k + 1);
	for (int i = 1; i < n; i++) {
		int a;
		scanf("%d", &a);

		graph[a].push_back(i);
	}

	cnt[func(0).second]--;

	std::sort(cnt + 1, cnt + index + 1);
	
	long long result = 0;
	for (int i = k; i >= 1; i--) {
		result += (long long)input[i] * cnt[i];
	}

	printf("%lld\n", result);
}