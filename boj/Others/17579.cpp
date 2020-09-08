#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <unordered_map>

bool check[110];
int input[110], weights[11], n, m;
std::vector<int> hap, X;
std::unordered_map<int, int> hashmap;

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

void func(int index, int result) {
	if (index == m + 1) {
		hap.push_back(aabs(result));
		return;
	}

	func(index + 1, result + weights[index]);
	func(index + 1, result);
	func(index + 1, result - weights[index]);
}

int main(void) {
	while (1) {
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;

		for (int i = 1; i <= n; i++) {
			scanf("%d", input + i);
		}

		for (int i = 1; i <= m; i++) {
			scanf("%d", weights + i);
		}

		hap.clear();

		func(1, 0);
		std::sort(hap.begin(), hap.end());
		hap.erase(std::unique(hap.begin(), hap.end()), hap.end());
		std::sort(input + 1, input + 1 + n);
		hashmap.clear();
		X.clear();

		memset(check, false, sizeof(check));
		int index = 0, tmp = 0;
		bool ff = false;

		for (int i = 1; i <= n; i++) {
			while (index < hap.size() && hap[index] < input[i])
				index++;
			if (hap[index] == input[i]) {
				check[i] = true;
				tmp++;
			}
			else if (ff == false) {
				ff = true;
				for (int j = 0; j < hap.size(); j++) {
					X.push_back(aabs(input[i] - hap[j]));
					X.push_back(aabs(input[i] + hap[j]));
					hashmap[hap[j]] = 1;
				}
			}

		}


		std::sort(X.begin(), X.end());
		X.erase(std::unique(X.begin(), X.end()), X.end());
		if (tmp == n) {
			printf("0\n");
			continue;
		}

		int result = -1;
		for (int i = 0; i < X.size(); i++) {
			bool flag = true;
			for (int j = 1; j <= n; j++) {
				if (check[j] == true)
					continue;

				int left = aabs(input[j] - X[i]), right = aabs(input[j] + X[i]);
				if (hashmap.find(left) == hashmap.end() && hashmap.find(right) == hashmap.end()) {
					flag = false;
					break;
				}
			}

			if (flag) {
				result = X[i];
				break;
			}
		}

		printf("%d\n", result);
	}
}