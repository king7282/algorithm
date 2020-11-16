#include <stdio.h>
#include <algorithm>
#include <vector>
 
std::pair<long long, long long> input[200010];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		long long w;
		scanf("%d %I64d", &n, &w);
 
		for (int i = 1; i <= n; i++) {
			scanf("%I64d", &input[i].first);
			input[i].second = i;
		}
 
		std::sort(input + 1, input + 1 + n);
 
		int s = 1, e = 1;
		long long sum = input[1].first, low = w / 2 + w % 2, upper = w;
		std::pair<long long, long long> result = std::make_pair(-1, -1);
		input[n + 1].first = 0;
		while (s <= n && e <= n) {
			if (sum < low) {
				sum += input[++e].first;
			}
			else if (sum > upper) {
				sum -= input[s++].first;
			}
			else {
				result.first = s;
				result.second = e;
				break;
			}
		}
 
		if (low <= sum && sum <= upper) {
			result.first = s;
			result.second = e;
		}
 
		if (result.first == -1) {
			printf("-1\n");
		}
		else {
			printf("%I64d\n", result.second - result.first + 1);
			std::vector<long long> tmp;
			for (int i = result.first; i <= result.second; i++) {
				tmp.push_back(input[i].second);
			}
 
			std::sort(tmp.begin(), tmp.end());
			for (int i = 0; i < tmp.size(); i++)
				printf("%I64d ", tmp[i]);
			printf("\n");
		}
	}
}