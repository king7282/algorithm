#include <iostream>
#include <map>
#include <string>

std::map<std::string, int> map;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();
	std::cout.tie();

	int n;
	std::cin >> n;

	for (int i = 1; i <= n; i++) {
		std::string input;
		std::cin >> input;

		if (map.find(input) == map.end())
			map[input] = 0;
		map[input]++;
	}

	std::string result = "NONE";

	for (auto it = map.begin(); it != map.end(); it++) {
		if (n - it->second < it->second)
			result = it->first;
	}

	std::cout << result;
}