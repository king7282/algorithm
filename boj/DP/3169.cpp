#include <stdio.h>
#include <algorithm>
#include <cstring>

int dp[2][6][6][27][6][27], value[6], n, input[1001];

int main(void) {
	for (int i = 1; i <= 5; i++)
		scanf("%d", value + i);

	scanf("%d", &n);
	getchar();

	for (int i = 1; i <= n; i++) {
		char tmp;
		scanf("%c", &tmp);
		input[i] = tmp - 'A';
	}

	memset(dp, 0, sizeof(dp));
	for (int num = n; num >= 1; num--) {
		for (int fc = 5; fc >= 0; fc--) {
			for (int sc = 5; sc >= 0; sc--) {
				for (int s = 'Z' - 'A' + 1; s >= 0; s--) {
					for (int tc = 5; tc >= 0; tc--) {
						for (int t = 'Z' - 'A' + 1; t >= 0; t--) {
							int &r = dp[num % 2][fc][sc][s][tc][t];
							r = 0;

							if (input[num - 1] == input[num]) {
								if (num == n)
									r = std::max(r, value[std::min(5, fc + 1)] + value[sc] + value[tc]);
								else
									r = std::max(r, dp[(num + 1) % 2][std::min(5, fc + 1)][sc][s][tc][t]);
							}
							else {
								if (num == n) {
									r = std::max(r, value[1] + value[sc] + value[tc] + value[fc]);
								}
								else
									r = std::max(r, dp[(num + 1) % 2][1][sc][s][tc][t] + value[fc]);
							}

							if (s == input[num]) {
								if (num == n)
									r = std::max(r, value[std::min(5, sc + 1)] + value[fc] + value[tc]);
								else
									r = std::max(r, dp[(num + 1) % 2][std::min(5, sc + 1)][fc][input[num - 1]][tc][t]);
							}
							else {
								if (num == n)
									r = std::max(r, value[1] + value[sc] + value[tc] + value[fc]);
								else
									r = std::max(r, dp[(num + 1) % 2][1][fc][input[num - 1]][tc][t] + value[sc]);
							}

							if (t == input[num]) {
								if (num == n)
									r = std::max(r, value[std::min(5, tc + 1)] + value[fc] + value[sc]);
								else
									r = std::max(r, dp[(num + 1) % 2][std::min(5, tc + 1)][fc][input[num - 1]][sc][s]);
							}
							else {
								if (num == n)
									r = std::max(r, value[1] + value[sc] + value[tc] + value[fc]);
								else
									r = std::max(r, dp[(num + 1) % 2][1][fc][input[num - 1]][sc][s] + value[tc]);
							}
						}
					}
				}
			}
		}
	}

	printf("%d\n", dp[1][0][0][0][0][0]);
}