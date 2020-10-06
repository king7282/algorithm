#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>

struct point {
	int index;
	long long a, b;
	double s;

	point(double s, long long a, long long b, int index) : s(s), a(a), b(b), index(index) {}
};

long long sum[100001], dp[2][100001];
int prev[201][100001];
std::vector<point> cht;

void insert(long long a, long long b, int index) {
	while (cht.size() > 0 && a == cht.back().a) {
		if (cht.back().b >= b)
			return;
		cht.pop_back();
	}

	double start = 0;
	while (cht.size() > 0) {
		double p = (double)(b - cht.back().b) / (cht.back().a - a);
		if (p <= cht.back().s)
			cht.pop_back();
		else {
			start = p;
			break;
		}
	}

	cht.push_back(point(start, a, b, index));
}

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 1; i <= n; i++) {
		long long a;
		scanf("%lld", &a);
		sum[i] = sum[i - 1] + a;
	}

	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++)
			dp[0][j] = dp[1][j];
		cht.clear();
		cht.push_back(point(0, 0, LLONG_MIN / 2, -1));
		insert(sum[i], dp[0][i] - sum[i] * sum[i], i);

		for (int j = i + 1; j <= n; j++) {
			int s = 0, e = cht.size() - 1, r = 0;
			while (s <= e) {
				int mid = (s + e) / 2;
				if (cht[mid].s <= sum[j]) {
					r = std::max(r, mid);
					s = mid + 1;
				}
				else
					e = mid - 1;
			}

			dp[1][j] = cht[r].a * sum[j] + cht[r].b;
			prev[i][j] = cht[r].index;

			insert(sum[j], dp[0][j] - sum[j] * sum[j], j);
		}
	}
	
	printf("%lld\n", dp[1][n]);
	int cur = n;

	std::vector<int> result;
	for (int i = k; i >= 1; i--) {
		cur = prev[i][cur];
		result.push_back(cur);
	}

	for (int i = result.size() - 1; i >= 0; i--) {
		printf("%d ", result[i]);
	}
	printf("\n");
}