#include <iostream>
#include <string>
#include <algorithm>

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::string input1, input2;
	char c;

	std::cin >> input1 >> c >> input2;

	if (c == '*') {
		std::cout << '1';
		for (int i = 0; i < input1.size() + input2.size() - 2; i++)
			std::cout << '0';
	}
	else {
		if (input1.size() == input2.size()) {
			std::cout << '2';
			for (int i = 0; i < input1.size() - 1; i++)
				std::cout << '0';
		}
		else {
			std::cout << '1';

			for (int i = 0; i < std::max(input1.size(), input2.size()) - 1; i++) {
				if (i == std::max(input1.size(), input2.size()) - std::min(input1.size(), input2.size()) - 1)
					std::cout << '1';
				else
					std::cout << '0';
			}
		}
	}
	
}