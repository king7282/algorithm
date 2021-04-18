#include <stdio.h>
#include <vector>

int main(void) {
	int a, b;
	scanf("%d %d", &a, &b);

	std::vector<int> input1, input2;

	while (a > 0) {
		input1.push_back(a % 10);
		a /= 10;
	}

	while (b > 0) {
		input2.push_back(b % 10);
		b /= 10;
	}

	int max1 = 0, min1 = 0, tmp1 = 0, tmp2 = 0;

	for (int i = (int)input1.size() - 1; i >= 0; i--) {
		if (input1[i] == 5)
			tmp1 = tmp1 * 10 + 6;
		else
			tmp1 = tmp1 * 10 + input1[i];

		if (input1[i] == 6)
			tmp2 = tmp2 * 10 + 5;
		else
			tmp2 = tmp2 * 10 + input1[i];
	}

	max1 += tmp1;
	min1 += tmp2;

	tmp1 = tmp2 = 0;

	for (int i = (int)input2.size() - 1; i >= 0; i--) {
		if (input2[i] == 5)
			tmp1 = tmp1 * 10 + 6;
		else
			tmp1 = tmp1 * 10 + input2[i];

		if (input2[i] == 6)
			tmp2 = tmp2 * 10 + 5;
		else
			tmp2 = tmp2 * 10 + input2[i];
	}

	max1 += tmp1;
	min1 += tmp2;

	printf("%d %d\n", min1, max1);
}