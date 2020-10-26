#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<long long> v;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();
	std::cout.tie();

	int n;
	std::cin >> n;

	for (int i = 1; i <= n; i++) {
		std::string input;
		std::cin >> input;

		if (input[0] == '-')
			continue;

		if (input.size() > 7)
			continue;

		long long tmp = 0;
		for (int j = 0; j < input.size(); j++) {
			tmp = tmp * 10 + (input[j] - '0');
		}

		v.push_back(tmp);
	}

	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());

	long long result = -1, prev = -1;
	for (int i = 0; i < v.size(); i++) {
		if (prev + 1 != v[i]) {
			result = prev + 1;
			break;
		}
		prev = v[i];
	}

	if (result == -1) {
		result = prev + 1;
	}

	std::cout << result;
}