#include <stdio.h>

int input[1000010], pi[1000010];

void getPi(int size) {
	pi[1] = 0;
	for (int i = 2; i <= size; i++) {
		int next = pi[i - 1];
		while (next > 0 && input[next + 1] != input[i]) {
			next = pi[next];
		}

		if (input[next + 1] == input[i])
			pi[i] = next + 1;
	}

}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &input[n - i + 1]);
	}

	getPi(n);

	int k = n + 1, p = n + 1;
	for (int i = 1; i <= n; i++) {
		if (((n - i) + (i - pi[i]) < k + p) || ((n - i) + (i - pi[i]) == k + p && (i - pi[i]) < p)) {
			p = i - pi[i];
			k = n - i;
		}

	}

	printf("%d %d\n", k, p);
}