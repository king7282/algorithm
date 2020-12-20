#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>

long long input[110];

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++)
		scanf("%lld", input + i);

	std::sort(input + 1, input + 1 + n);

	std::vector<long long> cur, next;
	cur.push_back(1);

	for (int i = 1; i <= n; i++) {
		for (long long j = input[i]; j <= INT_MAX; j *= input[i]) {
			next.clear();
			long long limits = INT_MAX;
			if (cur.size() >= k + 1)
				limits = cur[k];

			for (int z = 0; z < cur.size(); z++) {
				next.push_back(cur[z]);
			}

			for (int z = 0; z < cur.size() && cur[z] * input[i] <= limits; z++) {
				next.push_back(cur[z] * input[i]);
			}

			std::sort(next.begin(), next.end());
			next.erase(std::unique(next.begin(), next.end()), next.end());
			cur.clear();
			for (int z = 0; z <= k && z < next.size(); z++) {
				cur.push_back(next[z]);
			}
		}
	}

	printf("%d\n", cur[k]);
}

