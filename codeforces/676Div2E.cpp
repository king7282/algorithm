#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

std::vector<std::pair<long long, int>> input;
long long sum[200010];
int n;
bool sign[200010];

bool OK(int num) {
	if (n % 2 == 0 && num != n / 2)
		return true;
	if (n % 2 == 1 && num != n / 2 && num != n / 2 + 1)
		return true;

	memset(sign, false, sizeof(sign));
	for (int i = num; i < input.size(); i++)
		sign[input[i].second] = true;

	for (int i = 1; i < n; i++) {
		if (sign[i] == sign[i + 1])
			return true;
	}
	return false;
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		long long a;
		scanf("%I64d", &a);
		input.push_back(std::make_pair(a, i));
	}
	if (n == 1) {
		printf("%I64d\n", input[0].first);
		return 0;
	}

	if (n == 2) {
		printf("%I64d\n", -1 * (input[0].first + input[1].first));
		return 0;
	}

	std::sort(input.begin(), input.end());
	for (int i = 0; i < input.size(); i++)
		sum[i + 1] = sum[i] + input[i].first;

	int start = 0;
	if (n % 3 == 0) start = 1;
	else if (n % 3 == 1) start = 0;
	else start = 2;

	long long result = LLONG_MIN / 2;
	for (int i = start; i <= n; i += 3) {
		long long left = sum[i], right = sum[n] - sum[i];

		if (!OK(i)) {
			left = left - input[i - 1].first + input[i].first;
			right = right - input[i].first + input[i - 1].first;
		}

		result = std::max(result, right - left);
	}

	printf("%I64d\n", result);
}