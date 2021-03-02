#include <iostream>
#include <string>
#include <algorithm>

std::string input, input1, input2;
int SA[400010], pos[400010], lcp[400010], d, tmp[400010];

bool cmp(int a, int b) {
	if (pos[a] == pos[b]) {
		a += d;
		b += d;

		if (!(0 <= a && a < input.size() && 0 <= b && b < input.size()))
			return a > b;
		return pos[a] < pos[b];
	}
	return pos[a] < pos[b];
}
int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> input1 >> input2;


	for (int i = 0; i < input1.size(); i++)
		input.push_back(input1[i]);

	input.push_back('$');

	for (int i = 0; i < input2.size(); i++)
		input.push_back(input2[i]);

	for (int i = 0; i < input.size(); i++) {
		pos[i] = (int)input[i];
		SA[i] = i;
	}

	for (d = 1; d < input.size(); d *= 2) {
		std::sort(SA, SA + input.size(), cmp);

		tmp[SA[0]] = 0;
		for (int i = 1; i < input.size(); i++)
			tmp[SA[i]] = tmp[SA[i - 1]] + cmp(SA[i - 1], SA[i]);

		for (int i = 0; i < input.size(); i++)
			pos[SA[i]] = tmp[SA[i]];

		if (pos[SA[input.size() - 1]] == input.size() - 1)
			break;
	}

	for (int i = 0, k = 0; i < input.size(); i++, k = std::max(k - 1, 0)) {
		if (pos[i] == input.size() - 1)
			continue;

		for (int j = SA[pos[i] + 1]; input[j + k] == input[i + k]; k++);

		lcp[pos[i]] = k;
	}

	int max1 = -1, index = -1;
	for (int i = 0; i < input.size() - 1; i++) {
		if ((SA[i] < input1.size() && SA[i + 1] > input1.size()) || (SA[i] > input1.size() && SA[i + 1] < input1.size())) {
			if (lcp[i] > max1) {
				max1 = lcp[i];
				index = i;
			}
		}
	}

	std::cout << max1 << "\n";

	for (int i = SA[index]; i < SA[index] + max1; i++)
		std::cout << input[i];
	std::cout << "\n";
}
