#include <stdio.h>
#include <algorithm>
#include <cstring>

int input[1010];

int main(void) {
	while (1) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;

		memset(input, 0, sizeof(input));
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				int score;
				scanf("%d", &score);
				input[j] += score;
			}
		}


		std::sort(input + 1, input + 1 + n);
		printf("%d\n", input[n]);
	}
}