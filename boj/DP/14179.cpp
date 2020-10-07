#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

std::pair<long long, long long> input[5010];
long long C[5010][5010], dp[5010][2], sum[5010], front[5010], back[5010][5010];

void func(int num, int s, int e, int p, int q) {
	if (s > e)
		return;

	int mid = (s + e) / 2, index = -1;
	dp[mid][num % 2] = LLONG_MAX / 2;

	for (int i = p; i <= std::min(q, mid); i++) {
		long long tmp = dp[i - 1][(num - 1) % 2] + C[i][mid];
		if (tmp < dp[mid][num % 2]) {
			dp[mid][num % 2] = tmp;
			index = i;
		}
	}

	func(num, s, mid - 1, p, index);
	func(num, mid + 1, e, index, q);
}

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &input[i].first, &input[i].second);
	}

	std::sort(input + 1, input + 1 + n);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + input[i].second;

	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			back[i][j] = back[i][j - 1] + (input[j].first - input[i].first) * input[j].second;
		}
	}

	for (int i = 1; i <= n; i++) {
		long long sum1 = 0;
		for (int j = i; j <= n; j++) {
			front[j] = front[j - 1] + sum1 * (input[j].first - input[j - 1].first);
			sum1 += input[j].second;
		}

		for (int j = i + 1; j <= n; j++) {
			int s = i, e = j, r = i;
			while (s <= e) {
				int mid = (s + e) / 2;

				if (sum[mid - 1] - sum[i - 1] <= sum[j] - sum[mid - 1]) {
					r = std::max(r, mid);
					s = mid + 1;
				}
				else {
					e = mid - 1;
				}
 			}
			C[i][j] = front[r] + back[r][j];
		}
	}

	for (int i = 1; i <= n; i++)
		dp[i][0] = LLONG_MAX / 2;

	for (int i = 1; i <= k; i++) {
		func(i, i + 1, n, i, n);
		dp[i][i % 2] = 0;
	}

	printf("%lld\n", dp[n][k % 2]);
}