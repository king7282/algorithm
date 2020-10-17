#include <iostream>
#include <vector>
#include <string>
 
int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();
	std::cout.tie();
	int test;
	std::cin >> test;
 
	for (int t = 0; t < test; t++) {
		std::vector<char> v;
		std::string input;
 
		std::cin >> input;
 
		for (int i = 0; i < input.size(); i++) {
			v.push_back(input[i]);
			while (v.size() >= 2) {
				if (v[v.size() - 1] == 'B' && v[v.size() - 2] == 'A') {
					v.pop_back();
					v.pop_back();
				}
				else if (v[v.size() - 1] == 'B' && v[v.size() - 2] == 'B') {
					v.pop_back();
					v.pop_back();
				}
				else
					break;
			}
		}
 
		std::cout << v.size() << "\n";
 
	}
}