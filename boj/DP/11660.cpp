#include <stdio.h>
#include <algorithm>
#include <cstring>

long long sum[1100][1100];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		long long tmp = 0;
		for (int j = 1; j <= n; j++) {
			long long input;
			scanf("%lld", &input);

			tmp += input;

			sum[i][j] = sum[i - 1][j] + tmp;
		}
	}

	for (int i = 1; i <= m; i++) {
		int x1, y1, x2, y2;

		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		long long result = sum[x2][y2];

		result -= sum[x1 - 1][y2];
		result -= sum[x2][y1 - 1];
		result += sum[x1 - 1][y1 - 1];

		printf("%lld\n", result);
	}
}