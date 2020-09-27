#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
 
struct info {
	long long i, j, x;
	info(long long i, long long j, long long x) : i(i), j(j), x(x) {}
};
 
long long input[10010];
std::vector<info> result;
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		long long sum = 0;
		result.clear();
 
		for (int i = 1; i <= n; i++) {
			scanf("%I64d", input + i);
			sum += input[i];
		}
 
		if (sum % n != 0) {
			printf("-1\n");
			continue;
		}
 
		long long aver = sum / n;
		bool flag = true;
 
		for (int i = n; i >= 2 && flag; i--) {
			long long x = input[i] / i;
			if (x != 0)
				result.push_back(info(i, 1, x));
			input[i] -= x * i;
			input[1] += x * i;
 
			if (input[1] >= n - 1)
				break;
		}
 
		std::vector<std::pair<long long, int>> needs;
 
		for (int i = 2; i <= n; i++) {
			if (input[i] != 0)
				needs.push_back(std::make_pair(i - input[i] % i, i));
		}
 
		std::sort(needs.begin(), needs.end());
		for (int i = 0; i < needs.size() && flag; i++) {
			if (needs[i].first == 0)
				continue;
 
			if (input[needs[i].second] != 0) {
				result.push_back(info(1, needs[i].second, needs[i].first));
				input[1] -= needs[i].first;
				input[needs[i].second] += needs[i].first;
 
				if (input[1] < 0)
					while (1);
				result.push_back(info(needs[i].second, 1, input[needs[i].second] / needs[i].second));
				input[1] += input[needs[i].second];
				input[needs[i].second] -= input[needs[i].second];
			}
		}
 
		for (int i = 2; i <= n && flag; i++) {
			long long x = aver - input[i];
			if (x == 0)
				continue;
 
			result.push_back(info(1, i, x));
			input[1] -= x;
			input[i] += x;
 
			if (input[1] < 0)
				flag = false;
		}
 
		if (flag) {
			for (int i = 1; i <= n; i++)
				if (input[i] != aver)
					while (1);
			if (result.size() > 3 * n)
				while (1);
			printf("%d\n", result.size());
			for (int i = 0; i < result.size(); i++) {
				printf("%I64d %I64d %I64d\n", result[i].i, result[i].j, result[i].x);
			}
		}
		else {
			printf("-1\n");
		}
 
	}
}