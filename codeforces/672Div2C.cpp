#include <stdio.h>
#include <algorithm>

long long input[300010];
int n;

long long func(int num) {
	if (num == 0 || num == n + 1)
		return 0;
	
	if (input[num - 1] < input[num] && input[num] > input[num + 1])
		return input[num];

	if (input[num - 1] > input[num] && input[num] < input[num + 1])
		return -1 * input[num];
	return 0;
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int q;
		scanf("%d %d", &n, &q);

		for (int i = 1; i <= n; i++)
			scanf("%I64d", input + i);
		input[n + 1] = 0;

		long long result = 0;

		for (int i = 1; i <= n; i++) {
			result += func(i);
		}
		
		printf("%I64d\n", result);
		for (int i = 1; i <= q; i++) {
			int a, b;
			scanf("%d %d", &a, &b);

			result -= func(a);
			result -= func(a - 1);
			result -= func(a + 1);

			if (b - 1 != a && b - 1 != a + 1 && b - 1 != a - 1)
				result -= func(b - 1);
			if (b != a && b != a + 1 && b != a - 1)
				result -= func(b);
			if (b + 1 != a && b + 1 != a + 1 && b + 1 != a - 1)
				result -= func(b + 1);
			
			std::swap(input[a], input[b]);
			result += func(a - 1);
			result += func(a);
			result += func(a + 1);

			if(b - 1 != a && b - 1 != a + 1 && b - 1 != a - 1)
				result += func(b - 1);
			if (b != a && b != a + 1 && b != a - 1)
				result += func(b);
			if (b + 1 != a && b + 1 != a + 1 && b + 1 != a - 1)
				result += func(b + 1);


			printf("%I64d\n", result);
		}

	}
}