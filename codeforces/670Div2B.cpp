#include <stdio.h>
#include <algorithm>
#include <climits>
#include <vector>
 
int n;
long long input[100010];
std::vector<long long> plus, minus;
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		scanf("%d", &n);
 
		plus.clear();
		minus.clear();
		for (int i = 1; i <= n; i++) {
			scanf("%I64d", input + i);
			if (input[i] > 0)
				plus.push_back(input[i]);
			else
				minus.push_back(input[i]);
		}
 
		std::sort(plus.begin(), plus.end());
		std::sort(minus.begin(), minus.end());
		long long result = LLONG_MIN / 2;
		if (plus.size() == 0) {
			result = std::max(result, minus[minus.size() - 1] * minus[minus.size() - 2] * minus[minus.size() - 3] * minus[minus.size() - 4] * minus[minus.size() - 5]);
		}
		if (plus.size() >= 1 && minus.size() >= 4) {
			result = std::max(result, plus[plus.size() - 1] * minus[0] * minus[1] * minus[2] * minus[3]);
		}
		if (plus.size() >= 2 && minus.size() >= 3) {
			result = std::max(result, plus[0] * plus[1] * minus[minus.size() - 1] * minus[minus.size() - 2] * minus[minus.size() - 3]);
		}
		if (plus.size() >= 3 && minus.size() >= 2) {
			result = std::max(result, plus[plus.size() - 1] * plus[plus.size() - 2] * plus[plus.size() - 3] * minus[0] * minus[1]);
		}
		if (plus.size() >= 4 && minus.size() >= 1) {
			result = std::max(result, plus[0] * plus[1] * plus[2] * plus[3] * minus[minus.size() - 1]);
		}
		if (plus.size() >= 5) {
			result = std::max(result, plus[plus.size() - 1] * plus[plus.size() - 2] * plus[plus.size() - 3] * plus[plus.size() - 4] * plus[plus.size() - 5]);
		}
		printf("%I64d\n", result);
	}
}