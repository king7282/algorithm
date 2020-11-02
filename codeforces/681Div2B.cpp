#include <iostream>
#include <string>
#include <algorithm>
 
int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie();
	std::cout.tie();
 
	int test;
	std::cin >> test;
 
	for (int t = 0; t < test; t++) {
		int a, b;
		std::cin >> a >> b;
 
		std::string input;
		std::cin >> input;
 
		bool first = true;
		int cnt = 1, prev = 0;
		long long result = 0;
 
		for (int i = 1; i < input.size(); i++) {
			if (input[i] != input[i - 1]) {
				if (input[i] == '0') {
					if (first)
						result += a;
					else
						result += std::min(prev * b, a);
					first = false;
				}
				prev = cnt;
				cnt = 1;
			}
			else
				cnt++;
 
		}
 
		if (input.back() == '1') {
			if (first)
				result += a;
			else
				result += std::min(prev * b, a);
		}
 
		std::cout << result << "\n";
	}
}