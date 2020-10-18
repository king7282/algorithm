#include <stdio.h>
#include <algorithm>
#include <set>

std::multiset<std::pair<long long, std::pair<int, int>>> set;

long long func(int num, int p) {
	int cnt = num / p;
	if (num % p != 0)
		cnt++;

	int remain = cnt * p - num;

	// remain -> cnt - 1, p - remain -> cnt

	return (long long)(cnt - 1) * (cnt - 1) * remain + (long long)cnt * cnt * (p - remain);
}

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);
	long long result = 0;

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		set.insert(std::make_pair(func(a, 1) - func(a, 2), std::make_pair(a, 1)));
		result += func(a, 1);
	}

	int cur = n;

	while (cur < k) {
		auto top = *std::prev(set.end());
		set.erase(std::prev(set.end()));

		set.insert(std::make_pair(func(top.second.first, top.second.second + 1) - func(top.second.first, top.second.second + 2), std::make_pair(top.second.first, top.second.second + 1)));
		result -= top.first;
		cur++;
	}

	printf("%I64d\n", result);
}