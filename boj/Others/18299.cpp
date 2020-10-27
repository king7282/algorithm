#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <cstring>

bool OK[210];
std::list<int> location[210];
long long check[100010][4];
int s, l, n;
int input[100010], result[100010];

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();
	std::cout.tie();

	std::cin >> s >> l >> n;
	std::vector<std::string> X;

	for (int i = 1; i <= s; i++) {
		std::string a;
		std::cin >> a;
		X.push_back(a);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	for (int i = 1; i <= l; i++) {
		std::string a, b;
		std::cin >> a >> b;
		int index1 = std::lower_bound(X.begin(), X.end(), a) - X.begin(), index2 = std::lower_bound(X.begin(), X.end(), b) - X.begin();

		int tmp1 = index1 / 64, tmp2 = index2 / 64;
		check[index1][tmp2] |= (1LL << (index2 % 64));
		check[index2][tmp1] |= (1LL << (index1 % 64));
	}

	for (int i = 1; i <= n; i++) {
		std::string tmp;
		std::cin >> tmp;

		int index = std::lower_bound(X.begin(), X.end(), tmp) - X.begin();
		input[i] = index;
		location[index].push_back(i);
	}

	for (int i = 1; i <= n; i++) {
		memset(OK, false, sizeof(OK));

		long long cur[4] = {0, 0, 0, 0};
		std::vector<int> recursive;

		for (int j = 0; j < X.size(); j++)
			if (location[j].size() > 0)
				recursive.push_back(location[j].front());

		std::sort(recursive.begin(), recursive.end());

		for (int j = 0; j < recursive.size(); j++) {
			int value = input[recursive[j]];
			if ((cur[0] | check[value][0]) == check[value][0] && (cur[1] | check[value][1]) == check[value][1] && (cur[2] | check[value][2]) == check[value][2] && (cur[3] | check[value][3]) == check[value][3]) {
				OK[value] = true;
			}

			cur[value / 64] |= (1LL << (value % 64));
		}

		result[i] = -1;
		for (int j = 0; j < X.size(); j++) {
			if (OK[j] == true) {
				result[i] = j;
				location[j].pop_front();
				break;
			}
		}

	}

	for (int i = 1; i <= n; i++) {
		std::cout << X[result[i]] << " ";
	}
}