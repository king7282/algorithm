#include <stdio.h>
#include <algorithm>
#include <cstring>

long long map[21][21], n;
long long result;
bool check[21][21];

void solve(int cnt) {
	if (cnt == 5) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				result = std::max(result, map[i][j]);
		return;
	}

	long long backup[21][21] = { 0, };

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			backup[i][j] = map[i][j];

	memset(check, false, sizeof(check));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == 0)
				continue;

			for (int k = i; k >= 2; k--) {
				if (map[k - 1][j] == 0) {
					map[k - 1][j] = map[k][j];
					map[k][j] = 0;
				}
				else if (map[k][j] == map[k - 1][j] && check[k - 1][j] == false) {
					map[k - 1][j] *= 2;
					map[k][j] = 0;
					check[k - 1][j] = true;
					break;
				}
				else
					break;
			}
		}
	}

	solve(cnt + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			map[i][j] = backup[i][j];

	memset(check, false, sizeof(check));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == 0)
				continue;

			for (int k = j; k >= 2; k--) {
				if (map[i][k - 1] == 0) {
					map[i][k - 1] = map[i][k];
					map[i][k] = 0;
				}
				else if (map[i][k] == map[i][k - 1] && check[i][k - 1] == false) {
					map[i][k - 1] *= 2;
					map[i][k] = 0;
					check[i][k - 1] = true;
					break;
				}
				else
					break;
			}
		}
	}

	solve(cnt + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			map[i][j] = backup[i][j];

	memset(check, false, sizeof(check));
	for (int i = n; i >= 1; i--) {
		for (int j = n; j >= 1; j--) {
			if (map[i][j] == 0)
				continue;

			for (int k = i; k < n; k++) {
				if (map[k + 1][j] == 0) {
					map[k + 1][j] = map[k][j];
					map[k][j] = 0;
				}
				else if (map[k + 1][j] == map[k][j] && check[k + 1][j] == false) {
					map[k + 1][j] *= 2;
					map[k][j] = 0;
					check[k + 1][j] = true;
					break;
				}
				else
					break;
			}
		}
	}

	solve(cnt + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			map[i][j] = backup[i][j];

	memset(check, false, sizeof(check));
	for (int i = n; i >= 1; i--) {
		for (int j = n; j >= 1; j--) {
			if (map[i][j] == 0)
				continue;

			for (int k = j; k < n; k++) {
				if (map[i][k + 1] == 0) {
					map[i][k + 1] = map[i][k];
					map[i][k] = 0;
				}
				else if (map[i][k + 1] == map[i][k] && check[i][k + 1] == false) {
					map[i][k + 1] *= 2;
					map[i][k] = 0;
					check[i][k + 1] = true;
					break;
				}
				else
					break;
			}
		}
	}

	solve(cnt + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			map[i][j] = backup[i][j];
}

int main(void) {
	scanf("%lld", &n);

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%lld", &map[i][j]);

	solve(0);
	printf("%lld\n", result);
}