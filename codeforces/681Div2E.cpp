#include <stdio.h>
#include <algorithm>
#include <vector>
 
long long fac[16];
 
int main(void) {
	int n, q;
	scanf("%d %d", &n, &q);
 
	fac[0] = 1;
	for (int i = 1; i <= 15; i++)
		fac[i] = (fac[i - 1] * i);
 
	long long cur = 0;
 
	for (int i = 1; i <= q; i++) {
		int type;
		scanf("%d", &type);
 
		if (type == 1) {
			long long l, r;
			scanf("%I64d %I64d", &l, &r);
 
			std::vector<std::pair<int, int>> vec;
			long long result = 0;
			long long start = 0;
 
			for (int j = 1; j <= 15; j++) {
				if (fac[j] > cur) {
					start = n - (j - 1);
					break;
				}
			}
 
			if (r < start) {
				printf("%I64d\n", r * (r + 1) / 2 - l * (l - 1) / 2);
				continue;
			}
			else if (l < start) {
				result = start * (start - 1) / 2 - l * (l - 1) / 2;
				l = start;
			}
 
			std::vector<int> remain;
			for (int j = start; j <= n; j++)
				remain.push_back(j);
 
			for (int j = start; j <= n; j++) {
				int tmp = n - j;
				long long ttmp = cur / fac[tmp];
				int index = ttmp % remain.size();
 
				vec.push_back(std::make_pair(remain[index], j));
				remain.erase(remain.begin() + index);
			}
 
			for (int j = 0; j < vec.size(); j++) {
				if (l <= vec[j].second && vec[j].second <= r)
					result += vec[j].first;
			}
 
			printf("%I64d\n", result);
		}
		else {
			long long x;
			scanf("%I64d", &x);
			cur += x;
		}
	}
}