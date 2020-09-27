#include <stdio.h>
#include <vector>
#include <cstring>

bool check[100010];
std::vector<int> primes;
int cnt[10010];

void func(int num, std::vector<std::pair<int, int>> &result) {
	for (int i = 0; i < primes.size() && num > 1; i++) {
		int cnt = 0;
		while (num % primes[i] == 0) {
			num /= primes[i];
			cnt++;
		}

		if (cnt > 0) {
			result.push_back(std::make_pair(i, cnt));
		}
	}
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (long long i = 2; i <= n; i++) {
		if (check[i] == false) {
			for (long long j = i * i; j <= n; j += i)
				check[j] = true;
			primes.push_back(i);
		}
	}

	int result = -1;
	std::vector<std::pair<int, int>> input;
	
	func(n, input);
	for (int i = 2; i <= n; i++) {
		std::vector<std::pair<int, int>> tmp;
		memset(cnt, 0, sizeof(cnt));
		func(i, tmp);
		bool flag = true;
		for (int j = 0; j < tmp.size() && flag; j++) {
			cnt[tmp[j].first] += tmp[j].second;
			if (cnt[tmp[j].first] > 1)
				flag = false;
		}

		for (int j = 0; j < input.size() && flag; j++) {
			cnt[input[j].first] += input[j].second;
			if (cnt[input[j].first] > 1)
				flag = false;
		}

		if (flag) {
			result = i;
			break;
		}
	}

	printf("%d\n", result);

}