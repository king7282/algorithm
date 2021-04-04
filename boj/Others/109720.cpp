#include <stdio.h>
#include <algorithm>
#include <vector>

int main(void) {
	int n;
	scanf("%d", &n);

	std::vector<int> input;

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		input.push_back(a);
	}

	if (std::next_permutation(input.begin(), input.end())) {
		for (int i = 0; i < input.size(); i++)
			printf("%d ", input[i]);
		printf("\n");
	}
	else
		printf("-1\n");
}