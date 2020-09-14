#include <stdio.h>
#include <algorithm>
#include <vector>

std::vector<long long> primes1, primes2;
bool check[100010];

int main(void) {
	long long n, result = 1;
	scanf("%I64d", &n);
	if (n < 5000) {
		for (int i = 2; i <= n; i++) {
			printf("B %d\n", i);
			fflush(stdout);
			int a;
			scanf("%d", &a);
		}
		for (int i = 2; i <= n; i++) {
			printf("A %d\n", i);
			fflush(stdout);
			int a;
			scanf("%d", &a);
			if (a == 1)
				result = std::max(result, (long long)i);
		}
		printf("C %I64d\n", result);
	}
	else {
		for (long long i = 2; i <= n; i++) {
			if (check[i] == false) {
				for (long long j = i * i; j <= n; j += i)
					check[j] = true;
				if (i * i <= n)
					primes1.push_back(i);
				else
					primes2.push_back(i);
			}
		}

		int a;
		for (int i = 0; i < primes1.size(); i++) {
			printf("B %I64d\n", primes1[i]);
			fflush(stdout);
			scanf("%d", &a);

			long long tmp = 1;
			for (long long j = primes1[i]; j <= n; j *= primes1[i]) {
				printf("A %I64d\n", j);
				fflush(stdout);
				scanf("%d", &a);

				if (a == 1)
					tmp = std::max(tmp, j);
			}
			result *= tmp;
		}

		int sum, last;
		printf("A 1\n");
		fflush(stdout);
		scanf("%d", &sum);
		bool flag = false;

		for (int i = 0; i < primes2.size() && !flag; i++) {
			printf("B %I64d\n", primes2[i]);
			fflush(stdout);
			scanf("%d", &a);
			sum -= a;

			if (i % 100 == 0) {
				printf("A 1\n");
				fflush(stdout);
				scanf("%d", &a);

				if (a != sum) {
					flag = true;
					for (int j = std::max(i - 100 + 1, 0); j <= i; j++) {
						printf("A %I64d\n", primes2[j]);
						fflush(stdout);
						scanf("%d", &a);
						if (a == 1) {
							result *= primes2[j];
							break;
						}
					}
				}
				last = i;
			}
		}

		if (!flag) {
			for (int i = last + 1; i < primes2.size(); i++) {
				printf("A %I64d\n", primes2[i]);
				fflush(stdout);
				scanf("%d", &a);

				if (a == 1) {
					result *= primes2[i];
					break;
				}
			}
		}
		printf("C %I64d\n", result);
	}

}