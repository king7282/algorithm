#include <stdio.h>
#include <algorithm>

std::pair<int, int> lower[50010], upper[50010];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &lower[i].second, &lower[i].first);
	}

	scanf("%d", &lower[n + 1].second);
	lower[n + 1].first = 50020;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &upper[i].second, &upper[i].first);
	}

	scanf("%d", &upper[m + 1].second);
	upper[m + 1].first = 50020;


	long long result = 0, sum = 0, prev = 1;
	int index_lower = 1, index_upper = 1, cnt = 0;
	bool flag = false;

	for (int i = -1; i <= 50010; i++) {
		while (lower[index_lower].first <= i)
			index_lower++;

		while (upper[index_upper].first <= i)
			index_upper++;

		if (upper[index_upper].second - lower[index_lower].second > 0) {
			if (prev <= 0) {
				flag = true;
			}
			sum += upper[index_upper].second - lower[index_lower].second;
		}
		else if (upper[index_upper].second - lower[index_lower].second <= 0) {
			if (flag == true) {
				result += sum;
				flag = false;
				cnt++;
			}
			sum = 0;
		}
		prev = upper[index_upper].second - lower[index_lower].second;
	}


	printf("%d %lld\n", cnt, result);
}