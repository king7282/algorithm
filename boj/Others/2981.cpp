#include <stdio.h>
#include <algorithm>
#include <vector>

int input[110];

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}
int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	std::sort(input + 1, input + 1 + n);

	int result = input[2] - input[1];
	for (int i = 3; i <= n; i++)
		result = gcd(result, input[i] - input[i - 1]);

	std::vector<int> r;
	for (int i = 1; i * i <= result; i++) {
		if (result % i == 0) {
			r.push_back(i);
			if (i != result / i)
				r.push_back(result / i);
		}
	}

	std::sort(r.begin(), r.end());
	for (int i = 1; i < r.size(); i++)
		printf("%d ", r[i]);
	
}