#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

int track[100010];
std::string query[100010];
std::pair<int, std::string> input[100010];
std::map<std::string, std::vector<int>> map;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;

	int k;
	std::cin >> k;
	for (int i = 1; i <= k; i++) {
		std::cin >> input[i].first >> input[i].second;
	}

	std::sort(input + 1, input + 1 + k);
	for (int i = 1; i <= k; i++)
		map[input[i].second].push_back(input[i].first);
	
	std::cin >> k;
	int prev = 0, result = -1;
	for (int i = 1; i <= k; i++)
		std::cin >> query[i];

	for (int i = 1; i <= k && result == -1; i++) {
		track[i] = std::lower_bound(map[query[i]].begin(), map[query[i]].end(), prev) - map[query[i]].begin();

		if (track[i] == map[query[i]].size())
			result = 0;
		else
			prev = map[query[i]][track[i]];
	}

	if (result == 0)
		std::cout << "impossible\n";
	else {
		int prev = n - 1;
		for (int i = k; i >= 1 && result == -1; i--) {
			std::vector<int> &v = map[query[i]];
			int upper = std::upper_bound(v.begin(), v.end(), prev) - v.begin() - 1;
			if (track[i] < upper) {
				result = 0;
			}
			prev = v[track[i]];
		}

		if (result == 0) {
			std::cout << "ambiguous\n";
		}
		else
			std::cout << "unique\n";
	}
}
