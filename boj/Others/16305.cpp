#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <climits>

int month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int input[110];

int stod(int m, int d) {
	int result = 0;
	for (int i = 1; i < m; i++)
		result += month[i];
	result += d;

	return result;
}

std::pair<int, int> dtos(int days) {
	int tmp = 0;
	std::pair<int, int> result;

	for (int i = 1; i <= 12; i++) {
		tmp += month[i];
		if (tmp >= days) {
			result.first = i;
			days -= tmp - month[i];
			break;
		}
	}

	result.second = days;
	return result;
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		std::string a, b;
		std::cin >> a >> b;
		int m, d;

		m = (b[0] - '0') * 10 + b[1] - '0';
		d = (b[3] - '0') * 10 + b[4] - '0';
		input[i] = stod(m, d);
	}

	int result = -1, index = 0;
	int cur = stod(10, 28), finish = stod(10, 28);
	while (1) {
		int ttmp = INT_MAX / 2;
		for (int i = 1; i <= n; i++) {
			int dist = (cur - input[i] + 365) % 365;

			ttmp = std::min(ttmp, dist);
		}

		if (ttmp > result) {
			result = ttmp;
			index = cur;
		}

		cur++;
		if (cur == 366)
			cur = 1;
		if (cur == finish)
			break;
	}

	std::pair<int, int> rr = dtos(index);
	printf("%02d-%02d\n", rr.first, rr.second);
}