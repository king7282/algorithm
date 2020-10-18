#include <iostream>
#include <string>
 
int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();
	std::cout.tie();
 
	std::string input;
	std::cin >> input;
 
 
	std::cout << "3\n";
	std::cout << "L 2\n";
	std::cout << "R 2\n";
	std::cout << "R " << 2 * input.size() - 1 << "\n";
}