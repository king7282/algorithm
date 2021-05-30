#include <iostream>
#include <string>

int main(void) {
	std::cin.tie(0);
	std::ios::sync_with_stdio(false);
	
	std::string input;

	std::cin >> input;
	
	int result = 0;
	if (input[0] == '0') {
		if (input[1] == 'x') {
			for (int i = 2; i < input.size(); i++) {
				if (!('0' <= input[i] && input[i] <= '9'))
					result = result * 16 + input[i] - 'a' + 10;
				else
					result = result * 16 + input[i] - '0';
			}
		}
		else {
			for (int i = 1; i < input.size(); i++) {
				result = result * 8 + input[i] - '0';
			}
		}
	}
	else {
		for (int i = 0; i < input.size(); i++)
			result = result * 10 + input[i] - '0';
	}

	printf("%d\n", result);


}