#include <iostream>
#include <string>

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::string input;
	long long num;
	std::cin >> input >> num;

	long long result = 0;
	for (int i = 0; i < input.size(); i++) {
		int cur = input[i] - '0';

		if (cur > 9)
			cur = cur + '0' - 'A' + 10;
		result = result * num + cur;
	}

	std::cout << result;
}