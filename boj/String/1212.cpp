#include <iostream>
#include <string>

std::string trans[8] = { "000", "001", "010", "011", "100", "101", "110", "111" };

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	std::string input, result;
	std::cin >> input;

	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < trans[input[i] - '0'].size(); j++) {
			if (result.size() == 0 && trans[input[i] - '0'][j] == '0')
				continue;
			result.push_back(trans[input[i] - '0'][j]);
		}
	}

	if (result.size() == 0)
		result.push_back('0');
	std::cout << result;
}