#include <stdio.h>
#include <algorithm>
#include <climits>
#include <vector>

int input[310], n, m;

bool OK(int num) {
	int k = 1, sum = 0;

	for (int i = 1; i <= n; i++) {
		if (sum + input[i] > num) {
			k++;
			sum = 0;
		}
		sum += input[i];
	}

	return k <= m;
}

int main(void) {
	scanf("%d %d", &n, &m);

	int min1 = 0, sum = 0;

	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		min1 = std::max(min1, input[i]);
		sum += input[i];
	}

	int s = min1, e = sum, r = sum;

	while (s <= e) {
		int mid = (s + e) / 2;

		if (OK(mid)) {
			r = std::min(r, mid);
			e = mid - 1;
		}
		else
			s = mid + 1;
	}

	printf("%d\n", r);
	std::vector<int> result;
	sum = 0;
	int num = 0;

	for (int i = 1; i <= n; i++) {
		if (sum + input[i] > r) {
			sum = 0;
			result.push_back(num);
			num = 0;
		}
		sum += input[i];
		num++;
	}

	if (num != 0)
		result.push_back(num);

	if (result.size() < m) {
		int back = 0;

		while (back + result.size() < m) {
			back += result.back();
			result.pop_back();
		}

		while (result.size() < m - 1) {
			result.push_back(1);
			back--;
		}

		result.push_back(back);
	}

	for (int i = 0; i < result.size(); i++)
		printf("%d ", result[i]);
}