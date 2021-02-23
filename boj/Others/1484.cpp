#include <stdio.h>
#include <vector>
#include <algorithm>

std::vector<int> primes, result;

int main(void) {
	int g;
	scanf("%d", &g);

	for (int i = 1; i <= g; i++) {
		if (g % i == 0)
			primes.push_back(i);
	}

	for (int i = 0; i < primes.size(); i++) {
		int a2 = primes[i] + g / primes[i], b2 = primes[i] - g / primes[i];

		if (a2 % 2 != 0 || b2 <= 0 || b2 % 2 != 0)
			continue;

		result.push_back(a2 / 2);
	}

	std::sort(result.begin(), result.end());
	result.erase(std::unique(result.begin(), result.end()), result.end());

	if (result.size() == 0)
		printf("-1\n");
	else
		for (int i = 0; i < result.size(); i++)
			printf("%d\n", result[i]);
}