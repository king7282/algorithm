#include <iostream>
#include <string>
#include <algorithm>

int SA[500010], group[500010], d, tmp[500010], LCP[500010];
std::string input;

bool cmp(int a, int b) {
	if (group[a] == group[b]) {
		a += d;
		b += d;

		if (!(a < input.size() && b < input.size()))
			return a > b;
		return group[a] < group[b];
	}

	return group[a] < group[b];
}
int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> input;

	for (int i = 0; i < input.size(); i++) {
		SA[i] = i;
		group[i] = input[i] - 'a';
	}

	for (d = 1; d < input.size(); d *= 2) {
		std::sort(SA, SA + input.size(), cmp);

		tmp[SA[0]] = 0;
		for (int i = 1; i < input.size(); i++)
			tmp[SA[i]] = tmp[SA[i - 1]] + cmp(SA[i - 1], SA[i]);
		for (int i = 0; i < input.size(); i++)
			group[SA[i]] = tmp[SA[i]];

		if (group[SA[input.size() - 1]] == input.size() - 1)
			break;

	}

	for (int i = 0; i < input.size(); i++)
		std::cout << SA[i] + 1 << " ";
	std::cout << "\nx ";

	for (int i = 0, k = 0; i < input.size(); i++, k = std::max(k - 1, 0)) {
		if (group[i] == input.size() - 1)
			continue;

		for (int j = SA[group[i] + 1]; j + k < input.size() && i + k < input.size() && input[i + k] == input[j + k]; k++);

		LCP[group[i]] = k;
	}

	for (int i = 0; i < input.size() - 1; i++)
		std::cout << LCP[i] << " ";
}