#include <stdio.h>
#include <algorithm>
#include <climits>
#include <cstring>

long long w, n, input[500010], sum[500010];
int values[500010];

bool OK(long long limits) {
	memset(values, 0, sizeof(values));
	values[n + 1] = 1;
	int start = n;
	while (start >= 1) {
		if (sum[n] - sum[start - 1] >= limits && sum[n] - sum[start - 1] <= w) {
			values[start] = values[start + 1] + 1;
			start--;
			break;
		}
		values[start] = values[start + 1];
		start--;
	}

	if (start == 0) {
		if (values[1] - values[2] == 0)
			return false;
		return true;
	}

	int low = n, high = start;
	
	for (int i = start; i <= n; i++) {
		if (sum[i] - sum[start - 1] >= limits) {
			low = i - 1;
			break;
		}
	}

	for (int i = start; i <= n; i++) {
		if (sum[i] - sum[start - 1] <= w)
			high = i;
	}

	for (int i = start; i >= 1; i--) {
		while (low >= i && sum[low] - sum[i - 1] >= limits)
			low--;

		while (high >= i && sum[high] - sum[i - 1] > w)
			high--;

		if (low >= high)
			values[i] = values[i + 1];
		else {
			if (values[low + 2] - values[high + 2] == 0) {
				values[i] = values[i + 1];
			}
			else
				values[i] = values[i + 1] + 1;
		}
	}

	if (values[1] - values[2] == 0)
		return false;
	return true;
}

int main(void) {
	scanf("%lld %lld", &w, &n);

	for (int i = 1; i <= n; i++) {
		scanf("%lld", input + i);
		sum[i] = sum[i - 1] + input[i];
	}

	sum[n + 1] = sum[n];
	
	long long s = 1, e = std::min(w, sum[n]), r = 0;

	while (s <= e) {
		long long mid = (s + e) / 2;
		if (OK(mid)) {
			r = std::max(r, mid);
			s = mid + 1;
		}
		else
			e = mid - 1;
	}

	printf("%lld\n", (long long)(w - r) * (w - r));
}