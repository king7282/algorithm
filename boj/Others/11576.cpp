#include <stdio.h>
#include <vector>

int main(void) {
	int a, b;
	scanf("%d %d", &a, &b);

	int n, result = 0;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int input;
		scanf("%d", &input);

		result = result * a + input;
	}

	std::vector<int> v;

	while (result > 0) {
		v.push_back(result % b);
		result /= b;
	}

	for (int i = v.size() - 1; i >= 0; i--)
		printf("%d ", v[i]);
}