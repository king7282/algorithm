#include <stdio.h>
#include <map>
#include <algorithm>

int mov[6][2] = { {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}, {1, 0} };

int aabs(int num) {
	if (num < 0)
		return -1 * num;
	return num;
}

int main(void) {
	std::pair<int, int> finish;
	scanf("%d %d", &finish.first, &finish.second);

	if (finish.first == 0 && finish.second == 0)
		printf("1\n");
	else if (finish.first == 0 && finish.second == 1)
		printf("2\n");
	else if (finish.first == -1 && finish.second == 1)
		printf("3\n");
	else if (finish.first == -1 && finish.second == 0)
		printf("4\n");
	else if (finish.first == 0 && finish.second == -1)
		printf("5\n");
	else if (finish.first == 1 && finish.second == -1)
		printf("6\n");
	else if (finish.first == 1 && finish.second == 0)
		printf("7\n");
	else {
		int length = std::min(aabs(finish.first) + aabs(finish.second), aabs(finish.first) + aabs(finish.first + finish.second));
		std::pair<int, int> cur = std::make_pair(length - 1, -1 * (length - 1));

		int hap = length;
		long long cnt = 1, gap = 5;
		for (int i = 0; i < hap - 1; i++) {
			cnt += gap;
			gap += 6;
		}
		cnt++;

		for (int d = 0; d <= 5; d++) {
			if (d == 1) {
				for (int i = 1; i <= hap - 1; i++) {
					cur.first += mov[d][0], cur.second += mov[d][1];
					if (cur == finish) {
						printf("%lld\n", cnt);
						return 0;
					}
					cnt++;
				}
			}
			else {
				for (int i = 1; i <= hap; i++) {
					cur.first += mov[d][0], cur.second += mov[d][1];

					if (cur == finish) {
						printf("%d\n", cnt);
						return 0;
					}
					cnt++;
				}
			}
		}

		cur = std::make_pair(length, -1 * length);
		hap = length + 1;
		cnt = 1, gap = 5;
		for (int i = 0; i < hap - 1; i++) {
			cnt += gap;
			gap += 6;
		}
		cnt++;

		for (int d = 0; d <= 5; d++) {
			if (d == 1) {
				for (int i = 1; i <= hap - 1; i++) {
					cur.first += mov[d][0], cur.second += mov[d][1];
					if (cur == finish) {
						printf("%lld\n", cnt);
						return 0;
					}
					cnt++;
				}
			}
			else {
				for (int i = 1; i <= hap; i++) {
					cur.first += mov[d][0], cur.second += mov[d][1];

					if (cur == finish) {
						printf("%lld\n", cnt);
						return 0;
					}
					cnt++;
				}
			}
		}
	}
}