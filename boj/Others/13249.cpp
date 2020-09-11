#include <stdio.h>
#include <algorithm>

long long t, input[20], cur[20], direction[20], times[20];
int n;

long long func(int num) {
	long long result = 0;

	for (int i = 1; i <= n; i++) {
		cur[i] = input[i];
		times[i] = 0;
		if (((1 << (i - 1)) & num) != 0) {
			direction[i] = 1;
		}
		else
			direction[i] = 0;
	}

	for (int i = 0; ; i++) {
		direction[n + 1] = 0;
		bool flag = false;
		for (int j = 1; j <= n; j++) {
			if (direction[j] == 0 && direction[j + 1] == 1) {
				flag = true;
				long long left = cur[j], right = cur[j + 1], cur_time;

				if (times[j] < times[j + 1]) {
					left += times[j + 1] - times[j];
					cur_time = times[j + 1];
				}
				else {
					right -= times[j] - times[j + 1];
					cur_time = times[j];
				}

				long long diff = (right - left);

				if (diff % 2 == 0) {
					times[j] = times[j + 1] = cur_time + diff / 2;
					direction[j] = 1, direction[j + 1] = 0;
					if (cur_time + diff / 2 <= t) {
						result++;
					}

					cur[j] = cur[j + 1] = left + diff / 2;
				}
				else {
					times[j] = times[j + 1] = cur_time + (diff + 1) / 2;
					direction[j] = 1, direction[j + 1] = 0;
					if (cur_time + (diff + 1) / 2 <= t) {
						result++;
					}

					cur[j] = left + diff / 2;
					cur[j + 1] = right - diff / 2;
				}
			}
		}

		if (!flag)
			break;
	}

	return result;
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%lld", &input[i]);
	}

	std::sort(input + 1, input + 1 + n);

	scanf("%lld", &t);
	long long result = 0;
	for (int i = 0; i < (1 << n); i++) {
		result += func(i);
	}

	long long tmp = 1;

	for (int i = 1; i <= n; i++)
		tmp = tmp * 2LL;

	printf("%lf\n", result / (double)tmp);
}