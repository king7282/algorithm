#include <iostream>
#include <string>

int main(void) {
	std::string s;
	std::cin >> s;

	for (int i = 0; i < s.size(); i++)
		s[i] = s[i] - 'a' + 'A';

	std::cout << s;
}
