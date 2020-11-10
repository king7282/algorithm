#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <deque>

long long input[1010], result[1010];
std::deque<long long> aaa;
int n;

int main(void) {
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%lld", input + i);
		}

		if (n == 1) {
			printf("%lld\n", input[0] * 2);
			return 0;
		}
		else if (n == 2) {
			printf("%.6lf\n", input[0] + input[1] + 2 * sqrt(input[0] * input[1]));
			return 0;
		}

		std::sort(input, input + n);
		aaa.clear();

		aaa.push_back(input[n - 1]);
		int lower = 0, upper = n - 2;
		bool flag = false;

		while (lower <= upper) {
			if (!flag) {
				aaa.push_front(input[lower++]);
				if (lower > upper)
					break;
				aaa.push_back(input[lower++]);
			}
			else {
				aaa.push_front(input[upper--]);
				if (lower > upper)
					break;
				aaa.push_back(input[upper--]);
			}
			flag = (!flag);
		}

		for (int i = 0; i < n; i++) {
			result[i] = aaa.front();
			aaa.pop_front();
		}

		long double r1 = result[0];
		for (int i = 1; i < n; i++) {
			r1 += 2 * sqrt(result[i] * result[i - 1]);
		}
		r1 += result[n - 1];

		
		aaa.clear();

		aaa.push_back(input[0]);
		lower = 1, upper = n - 1;
		flag = true;

		while (lower <= upper) {
			if (!flag) {
				aaa.push_front(input[lower++]);
				if (lower > upper)
					break;
				aaa.push_back(input[lower++]);
			}
			else {
				aaa.push_front(input[upper--]);
				if (lower > upper)
					break;
				aaa.push_back(input[upper--]);
			}
			flag = (!flag);
		}

		for (int i = 0; i < n; i++) {
			result[i] = aaa.front();
			aaa.pop_front();
		}

		long double r2 = result[0];
		for (int i = 1; i < n; i++) {
			r2 += 2 * sqrt(result[i] * result[i - 1]);
		}
		r2 += result[n - 1];


		printf("%.6Lf\n", std::min(r1, r2));
}