#include <stdio.h>
#include <vector>
#include <algorithm>

bool check[40010];
std::vector<long long> primes;

int main(void) {
	for (long long i = 2; i <= 40000; i++) {
		if (check[i] == false) {
			for (long long j = i * i; j <= 40000; j += i) {
				check[j] = true;
			}
			primes.push_back(i);
		}
	}

	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		long long n;
		scanf("%I64d", &n);

		long long tmp = n, sum = 0;
		std::vector<long long> v;

		for (long long i = 0; i < primes.size() && tmp > 1; i++) {
			long long cnt = 0;
			while (tmp % primes[i] == 0) {
				tmp /= primes[i];
				cnt++;
			}

			if (cnt > 0)
				v.push_back(primes[i]);
			sum += cnt;
		}

		if (tmp > 1) {
			v.push_back(tmp);
			sum++;
		}

		std::sort(v.begin(), v.end());
		int result = 0;
		if (v.size() == 1 || (v.size() == 2 && sum == 2)) {
			if (v.size() == 2 && sum == 2)
				result = 1;
			for (long long i = 2; i * i <= n; i++) {
				if (n % i == 0) {
					printf("%I64d ", i);
					if (n / i != i)
						printf("%I64d ", n / i);
				}
			}
			printf("%I64d\n", n);
		}
		else {
			std::vector<long long> tt;

			for (int i = 1; i < v.size(); i++)
				tt.push_back(v[i - 1] * v[i]);
			if(v.size() != 2)
				tt.push_back(v.back() * v[0]);

			std::vector<std::vector<long long>> divisor;
			divisor.resize(v.size());

			for (long long i = 1; i * i <= n; i++) {
				if (n % i == 0) {
					if(i != 1) {
						for (int j = 0; j < v.size(); j++) {
							if (i % v[j] == 0) {
								if (i != v[j] * v[(j + 1) % v.size()] && i != tt.back())
									divisor[j].push_back(i);
								break;
							}
						}
					}

					if (n / i != i) {
						for (int j = 0; j < v.size(); j++) {
							if ((n / i) % v[j] == 0) {
								if ((n / i) != v[j] * v[(j + 1) % v.size()] && n / i != tt.back())
									divisor[j].push_back(n / i);
								break;
							}
						}
					}
				}
			}
			
			for (int i = 0; i < v.size(); i++) {
				for (int j = 0; j < divisor[i].size(); j++)
					printf("%I64d ", divisor[i][j]);
				if(!(v.size() == 2 && i == 1))
					printf("%I64d ", tt[i]);
			}
			printf("\n");
		}

		printf("%d\n", result);
	}
}