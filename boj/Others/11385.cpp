#include <string>
#include <iostream>
#include <stdio.h>
#include <complex>
#include <vector>
#include <algorithm>
#include <cassert>
#define M_PI 3.14159265358979323846

typedef std::complex<double> base;

template<typename T>
struct FFT {
	void fft(std::vector<base> &a, bool inv = false) {
		int n = (int)a.size();
		for (int i = 1, j = 0; i < n; i++) {
			int bit = n >> 1;
			for (; j >= bit; bit >>= 1)j -= bit;
			j += bit;
			if (i < j)swap(a[i], a[j]);
		}
		std::vector<base> root(n / 2);
		double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
		for (int i = 0; i < n / 2; i++)root[i] = base(cos(ang*i), sin(ang*i));
		for (int idx = 2; idx <= n; idx <<= 1) {
			int step = n / idx;
			for (int i = 0; i < n; i += idx) {
				for (int j = 0; j < idx / 2; j++) {
					base u = a[i + j], v = a[i + j + idx / 2] * root[step*j];
					a[i + j] = u + v;
					a[i + j + idx / 2] = u - v;
				}
			}
		}
		if (inv) {
			for (auto &i : a) i /= n;
		}
	}
	std::vector<T> big_multiply(const std::vector<T> &a, const std::vector<T> &b) {
		const long long B = 14LL;
		const long long mod = (1LL << B) - 1LL;

		std::vector<base> a1, a2, b1, b2;
		std::vector<base> r1, r2, r3;

		long long siz = 1;
		while (siz < a.size() || siz < b.size())siz <<= 1; siz <<= 1;

		a1.resize(siz); a2.resize(siz);
		b1.resize(siz); b2.resize(siz);
		r1.resize(siz); r2.resize(siz); r3.resize(siz);

		for (int i = 0; i < a.size(); i++) {
			a1[i] = a[i] >> B;
			a2[i] = a[i] & mod;
		}
		for (int i = 0; i < b.size(); i++) {
			b1[i] = b[i] >> B;
			b2[i] = b[i] & mod;
		}

		fft(a1); fft(a2);
		fft(b1); fft(b2);

		for (int i = 0; i < siz; i++) {
			r1[i] = a1[i] * b1[i];
			r2[i] = a1[i] * b2[i] + a2[i] * b1[i];
			r3[i] = a2[i] * b2[i];
		}

		fft(r1, true);
		fft(r2, true);
		fft(r3, true);

		std::vector<T> ret;
		ret.resize(siz);
		long long x = (1LL << B);
		long long sqx = x * x;
		for (int i = 0; i < siz; i++) {
			ret[i] = (T)(r3[i].real() + 0.5);
			ret[i] += (T)(r2[i].real() + 0.5)*x;
			ret[i] += (T)(r1[i].real() + 0.5)*sqx;
		}
		return ret;
	}
};

int main() {
	FFT<long long> fft;

	int n, m;
	std::vector<long long> v1, v2;

	scanf("%d %d", &n, &m);

	for (int i = 0; i <= n; i++) {
		long long a;
		scanf("%lld", &a);
		v1.push_back(a);
	}

	for (int i = 0; i <= m; i++) {
		long long a;
		scanf("%lld", &a);
		v2.push_back(a);
	}

	std::vector<long long> result = fft.big_multiply(v1, v2);

	long long r = 0;
	for (int i = 0; i < result.size(); i++)
		r ^= result[i];
	printf("%lld\n", r);
}
