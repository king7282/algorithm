#include <stdio.h>
#include <climits>
#include <algorithm>

std::pair<int, int> input[1010];

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);
	int min1 = INT_MAX / 2;

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &input[i].first, &input[i].second);
		min1 = std::min(min1, input[i].first);
	}

	std::sort(input + 1, input + 1 + n);

	int result = INT_MAX / 2;
	if (k >= 1) {
		int tmp = 0;
		for (int i = 1; i <= n; i++) {
			tmp = std::max(tmp, (input[i].first - min1) * input[i].second + 30);
		}
		result = std::min(result, tmp);
	}
	if (k >= 2) {
		for (int i = min1 + 1; i <= 100; i++) {
			int tmp1 = 0, tmp2 = 0;
			for (int j = 1; j <= n; j++) {
				if (input[j].first < i) {
					tmp1 = std::max(tmp1, (input[j].first - min1) * input[j].second + 30);
				}
				else{
					if(tmp1 < (input[j].first - min1) * input[j].second + 30)
						tmp2 = std::max(tmp2, (input[j].first - i) * input[j].second + 30);
				}
			}
			result = std::min(result, tmp1 + tmp2);
		}
	}
	if (k >= 3) {
		for (int i = min1 + 1; i <= 100; i++) {
			for (int j = i + 1; j <= 100; j++) {
				int tmp1 = 0, tmp2 = 0, tmp3 = 0;

				for (int k = 1; k <= n; k++) {
					if (input[k].first < i) {
						tmp1 = std::max(tmp1, (input[k].first - min1) * input[k].second + 30);
					}
					else if (input[k].first < j) {
						if(tmp1 < std::max(tmp1, (input[k].first - min1) * input[k].second + 30))
							tmp2 = std::max(tmp2, (input[k].first - i) * input[k].second + 30);
					}
					else {
						if(tmp1 < std::max(tmp1, (input[k].first - min1) * input[k].second + 30) && tmp2 < std::max(tmp2, (input[k].first - i) * input[k].second + 30))
							tmp3 = std::max(tmp3, (input[k].first - j) * input[k].second + 30);
					}
				}

				result = std::min(result, tmp1 + tmp2 + tmp3);
			}
		}
	}

	printf("%d\n", result);
}