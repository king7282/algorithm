#include <stdio.h>

bool primes[246913];

int main(void) {
	for (long long i = 2; i <= 246912; i++) {
		if (primes[i] == false) {
			for (long long j = i * i; j <= 246912; j += i) {
				primes[j] = true;
			}
		}
	}

	while (1) {
		int n, r = 0;
		scanf("%d", &n);

		if (n == 0)
			break;

		for (int i = n + 1; i <= 2 * n; i++) {
			if (primes[i] == false)
				r++;
		}

		printf("%d\n", r);
	}
}