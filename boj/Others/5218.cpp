#include <iostream>
#include <string>
#include <vector>

int main(void) {
	int test;
	std::cin >> test;

	for (int t = 0; t < test; t++) {
		std::string a, b;
		std::cin >> a >> b;
		
		printf("Distances: ");
		for (int i = 0; i < a.size(); i++) {
			int r = b[i] - a[i];
			if (r < 0)
				r += 26;

			printf("%d ", r);
		}
		printf("\n");
	}
}