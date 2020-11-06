#include <iostream>
#include <string>

std::string input;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();

	int test;
	std::cin >> test;
	for (int t = 0; t < test; t++) {
		std::cin >> input;

		switch (input.back()) {
		case 'a':
			input.push_back('s');
			break;
		case 'i':
		case 'y':
			input.pop_back();
			input.push_back('i');
			input.push_back('o');
			input.push_back('s');
			break;
		case 'l':
			input.push_back('e');
			input.push_back('s');
			break;
		case 'n':
			input.pop_back();
			input.push_back('a');
			input.push_back('n');
			input.push_back('e');
			input.push_back('s');
			break;
		case 'e':
			if (input.size() >= 2 && input[input.size() - 2] == 'n') {
				input.pop_back();
				input.pop_back();
				input.push_back('a');
				input.push_back('n');
				input.push_back('e');
				input.push_back('s');
			}
			else {
				input.push_back('u');
				input.push_back('s');
			}
			break;
		case 'o':
			input.push_back('s');
			break;
		case 'r':
			input.push_back('e');
			input.push_back('s');
			break;
		case 't':
			input.push_back('a');
			input.push_back('s');
			break;
		case 'u':
			input.push_back('s');
			break;
		case 'v':
			input.push_back('e');
			input.push_back('s');
			break;
		case 'w':
			input.push_back('a');
			input.push_back('s');
			break;
		default:
			input.push_back('u');
			input.push_back('s');
		}

		std::cout << input << "\n";
	}
}