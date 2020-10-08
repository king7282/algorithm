#include <string>
#include <stdio.h>
#include <complex>
#include <vector>
#include <algorithm>
#include <cstring>
#include <assert.h>
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
		for (int idx = 2; idx <= n; idx <<= 1) {
			double ang = 2 * M_PI / idx * (inv ? -1 : 1);
			base x(cos(ang), sin(ang));
			for (int i = 0; i < n; i += idx) {
				base w(1);
				for (int j = 0; j < idx / 2; j++) {
					base u = a[i + j], v = a[i + j + idx / 2] * w;
					a[i + j] = u + v;
					a[i + j + idx / 2] = u - v;
					w *= x;
				}
			}
		}
		if (inv) {
			for (auto &i : a) i /= n;
		}
	}
	std::vector<T> multiply(const std::vector<T> &a, const std::vector<T> &b) {
		std::vector<base> A(a.begin(), a.end()), B(b.begin(), b.end());
		int n = 1, N = std::max(A.size(), B.size());
		while (n < N)n <<= 1;
		n <<= 1;
		A.resize(n); B.resize(n);
		fft(A);
		fft(B);
		for (int i = 0; i < n; i++)
			A[i] *= B[i];
		fft(A, true);
		std::vector<T> res;
		res.resize(n);
		for (int i = 0; i < n; i++)
			res[i] = (T)(A[i].real() + (A[i].real() > 0 ? 0.5 : -0.5));
		return res;
	}
};

long long check[1000010];
long long check2[1000010];
std::vector<long long> v1;

int main(void) {
	FFT<long long> fft;
	int n;
	scanf("%d", &n);

	for (long long i = 1; i < n; i++) {
		check[(i * i) % n]++;
	}

	for (int i = 0; i < n; i++) {
		v1.push_back(check[i]);
	}

	std::vector<long long> r = fft.multiply(v1, v1);

	for (int i = 0; i < r.size(); i++) {
		if (i % 2 == 0) {
			check2[i % n] += (r[i] - check[i / 2]) / 2 + check[i / 2];

		}
		else {
			check2[i % n] += r[i] / 2;
		}
	}

	long long result = 0;
	for (long long i = 1; i < n; i++) {
		result += check2[(i * i) % n];
	}

	printf("%lld\n", result);
}