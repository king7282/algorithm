#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>

std::pair<long long, long long> input[41];
std::vector<long long> X, primes[12];
long long result, result1;

long long pow1(long long l, long long p, long long mod) {
	if (p == 0)
		return 1;
	if (p == 1)
		return l;

	long long tmp = pow1(l, p / 2, mod);
	tmp = (tmp * tmp) % mod;

	if (p % 2 == 1)
		tmp = (tmp * l) % mod;

	return tmp;
}

long long euler(long long a) {
	long long result = 1;
	for (int i = 0; i < X.size(); i++) {
		if (a % X[i] == 0)
			result = (result * (X[i] - 1));
	}

	return result;
}

std::pair<long long, long long> remainder(std::pair<long long, long long> a, std::pair<long long, long long> b) {
	if (a.first == 1) {
		return b;
	}
	else if (b.first == 1) {
		return a;
	}

	long long n1 = b.first, n2 = a.first, a1 = a.second, a2 = b.second;
	long long s1 = pow1(n1 % a.first, (euler(a.first) - 1), a.first), s2 = pow1(n2 % b.first, (euler(b.first) - 1), b.first);
	
	std::pair<long long, long long> result;
	result.first = a.first * b.first;
	result.second = (n1 * a1 % result.first * s1 % result.first + n2 * a2 % result.first * s2 % result.first) % result.first;
	return result;
}

void func(int index, std::pair<long long, long long> p, long long max1, long long ccnt) {
	if (index == X.size()) {
		if (result1 > ccnt)
			return;
		if (result1 == ccnt) {
			if (max1 <= p.second) {
				result = std::min(result, p.second);
				return;
			}


			long long tmp = (max1 - p.second) / p.first;
			if ((max1 - p.second) % p.first != 0)
				tmp++;
			result = std::min(result, tmp * p.first + p.second);
		}
		else if(result1 < ccnt){
			result1 = ccnt;
			if (max1 <= p.second) {
				result = p.second;
				return;
			}


			long long tmp = (max1 - p.second) / p.first;
			if ((max1 - p.second) % p.first != 0)
				tmp++;
			result = tmp * p.first + p.second;
		}
		return;
	}

	for (int i = 0; i < primes[index].size(); i++) {
		long long cnt = 0;
		for (int j = 0; j <= i; j++) {
			if (primes[index][i] % X[index] == primes[index][j] % X[index])
				cnt++;
		}

		func(index + 1, remainder(p, std::make_pair(X[index], primes[index][i] % X[index])), std::max(max1, primes[index][i]), ccnt + cnt);
	}
}

int main(void) {
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%lld %lld", &input[i].first, &input[i].second);
		X.push_back(input[i].second);
	}

	std::sort(X.begin(), X.end());
	X.erase(std::unique(X.begin(), X.end()), X.end());

	for (int i = 1; i <= n; i++) {
		int index = std::lower_bound(X.begin(), X.end(), input[i].second) - X.begin();
		primes[index].push_back(input[i].first);
	}

	for (int i = 0; i < X.size(); i++) {
		std::sort(primes[i].begin(), primes[i].end());
	}

	result1 = 0;
	result = LLONG_MAX;
	func(0, std::make_pair(1, 0), 0, 0);

	printf("%lld %d\n", result, result1);
}