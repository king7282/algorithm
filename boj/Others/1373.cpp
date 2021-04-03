#include <iostream>
#include <string>
#include <algorithm>

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::string input, result;

	std::cin >> input;

	for (int i = (int)input.size() - 1; i >= 0; i -= 3) {
		int tmp = 0, x = 1;

		for (int j = i; j > std::max(i - 3, -1); j--) {
			tmp += (input[j] - '0') * x;
			x *= 2;
		}

		result.push_back(tmp + '0');
	}

	for (int i = result.size() - 1; i >= 0; i--)
		std::cout << result[i];

}