#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

std::vector<int> v[6];
int C[6][200010], dp[6][200010], limits;

void func(int num, int s, int e, int p, int q) {
	if (s > e)
		return;
	if (e - s + 1 <= num) {
		for (int mid = s; mid <= e; mid++) {
			int index = -1;
			dp[num][mid] = INT_MIN / 2;

			for (int i = p; i <= std::min(mid / num, q); i++) {
				if (dp[num - 1][mid - num * i] < limits)
					continue;

				int tmp = dp[num - 1][mid - num * i] + C[num][i];
				if (tmp >= dp[num][mid]) {
					dp[num][mid] = tmp;
					index = i;
				}
			}
		}
		return;
	}

	int a = (s + e) / 2, b = a + num - 1;
	if (b > e) {
		b = e;
		a = e - num + 1;
	}

	bool flag = false;
	for (int mid = a; mid <= b; mid++) {
		int index = -1;
		dp[num][mid] = INT_MIN / 2;

		for (int i = p; i <= std::min(mid / num, q); i++) {
			if (dp[num - 1][mid - num * i] < limits)
				continue;

			int tmp = dp[num - 1][mid - num * i] + C[num][i];
			if (tmp > dp[num][mid]) {
				dp[num][mid] = tmp;
				index = i;
			}
		}

		if(index != -1){
			func(num, s, mid - 1, p, index);
			func(num, mid + 1, e, index, q);
			flag = true;
			break;
		}
	}

	if (!flag) {
		for (int i = a + 1; i <= e; i++)
			dp[num][i] = INT_MIN / 2;
		func(num, s, a - 1, p, q);
	}
}

int main(void) {
	int lo, hi, m;
	scanf("%d %d %d", &lo, &hi, &m);
	int sum = 0;

	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a == 0) {
			sum = sum + std::max(b, 0);
		}
		else {
			v[a].push_back(b);
		}

		if (b < 0)
			limits += b;
	}

	for (int i = 1; i <= 5; i++) {
		std::sort(v[i].begin(), v[i].end());
		for (int j = v[i].size() - 1; j >= 0; j--) {
			C[i][v[i].size() - j] = C[i][v[i].size() - j - 1] + v[i][j];
		}
	}

	for (int j = 0; j <= 5; j++) {
		for (int i = 1; i <= hi; i++)
			dp[j][i] = INT_MIN / 2;
	}

	int sum1 = 0;
	for (int i = 1; i <= 5; i++) {
		sum1 += v[i].size() * i;
		func(i, 1, std::min(sum1, hi), 0, v[i].size());
	}

	int result = INT_MIN / 2;
	for (int i = lo; i <= hi; i++) {
		for (int j = 1; j <= 5; j++)
			result = std::max(result, dp[j][i]);
	}
	printf("%d\n", result + sum);
}