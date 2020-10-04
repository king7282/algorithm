#include <stdio.h>
#include <algorithm>
#include <vector>
 
long long map[110][110];
 
long long aabs(long long num) {
	if (num < 0)
		return -1 * num;
	return num;
}
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, m;
		scanf("%d %d", &n, &m);
 
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%I64d", &map[i][j]);
			}
		}
 
		long long result = 0;
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= m / 2; j++) {
				long long a1 = map[i][j], a2 = map[n - i + 1][j], a3 = map[i][m - j + 1], a4 = map[n - i + 1][m - j + 1];
				std::vector<long long> v;
				v.push_back(a1); v.push_back(a2); v.push_back(a3); v.push_back(a4);
				std::sort(v.begin(), v.end());
 
				long long mid = v[v.size() / 2];
				result += aabs(a1 - mid) + aabs(a2 - mid) + aabs(a3 - mid) + aabs(a4 - mid);
			}
		}
 
		if (n % 2 == 1) {
			int cur = n / 2 + 1;
			for (int i = 1; i <= m / 2; i++) {
				long long a1 = map[cur][i], a2 = map[cur][m - i + 1];
				std::vector<long long> v;
				v.push_back(a1); v.push_back(a2);
				std::sort(v.begin(), v.end());
 
				long long mid = v[v.size() / 2];
				result += aabs(a1 - mid) + aabs(a2 - mid);
			}
		}
 
		if (m % 2 == 1) {
			int cur = m / 2 + 1;
			for (int i = 1; i <= n / 2; i++) {
				long long a1 = map[i][cur], a2 = map[n - i + 1][cur];
				std::vector<long long> v;
				v.push_back(a1); v.push_back(a2);
				std::sort(v.begin(), v.end());
 
				long long mid = v[v.size() / 2];
				result += aabs(a1 - mid) + aabs(a2 - mid);
			}
		}
		printf("%I64d\n", result);
	}
}