#include <stdio.h>
#include <algorithm>
#include <climits>

std::pair<int, int> input[300010];
int n;

bool OK(int num) {
	int index = 1;

	while (index <= n) {
		if (input[index].second * 2<= num)
			index++;
		else
			break;
	}

	if (index == n + 1)
		return true;

	int min1 = INT_MAX / 2, max1 = -1;
	while (index <= n) {
		int tmp_min = std::min(min1, input[index].second), tmp_max = std::max(max1, input[index].second);
		if (tmp_max - tmp_min <= num) {
			index++;
			min1 = tmp_min;
			max1 = tmp_max;
		}
		else
			break;
	}

	if (index == n + 1)
		return true;

	int min2 = INT_MAX / 2, max2 = -1;
	while (index <= n) {
		int tmp_min = std::min(min2, input[index].second), tmp_max = std::max(max2, input[index].second);
		if (tmp_max - tmp_min <= num) {
			index++;
			min2 = tmp_min;
			max2 = tmp_max;
		}
		else
			break;
	}

	if (index != n + 1)
		return false;

	if (std::min(min1, max1 - num) <= min2)
		return true;
	return false;
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &input[i].first, &input[i].second);
	}

	std::sort(input + 1, input + 1 + n);

	int s = 0, e = 1000000000, r = 1000000000;
	if (input[1].first == 0)
		s = 2 * input[1].second;

	while (s <= e) {
		int mid = (s + e) / 2;
		if (OK(mid)) {
			e = mid - 1;
			r = std::min(r, mid);
		}
		else
			s = mid + 1;
	}

	printf("%.1lf\n", r / 2.0);
}