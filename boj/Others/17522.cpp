#include <stdio.h>
#include <algorithm>
#include <set>
#include <climits>

std::pair<long long, long long> input[300010], front[300010], rear[300010];
int n;

bool OK(long long num) {

	int end = 1;
	while (end <= n && input[1].first + num >= input[end].first)
		end++;

	if (rear[end].second - rear[end].first <= num)
		return true;


	for (int i = 2; i <= n; i++) {
		
		while (end <= n && input[i].first + num >= input[end].first) {
			end++;
		}

		if (std::max(front[i - 1].second, rear[end].second) - std::min(front[i - 1].first, rear[end].first) <= num)
			return true;
	}
	
	return false;
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%lld %lld", &input[i].first, &input[i].second);

	std::sort(input + 1, input + 1 + n);

	front[0].first = rear[n + 1].first = LLONG_MAX / 2;
	front[0].second = rear[n + 1].second = LLONG_MIN / 2;
	for (int i = 1; i <= n; i++) {
		front[i].first = std::min(front[i - 1].first, input[i].second);
		front[i].second = std::max(front[i - 1].second, input[i].second);

		rear[n - i + 1].first = std::min(rear[n - i + 2].first, input[n - i + 1].second);
		rear[n - i + 1].second = std::max(rear[n - i + 2].second, input[n - i + 1].second);
	}

	long long s = 0, e = INT_MAX, r = INT_MAX;

	while (s <= e) {
		long long mid = (s + e) / 2;
		if (OK(mid)) {
			e = mid - 1;
			r = std::min(r, mid);
		}
		else
			s = mid + 1;
	}

	printf("%.1lf\n", r / 2.0);
}