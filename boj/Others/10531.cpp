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

bool check[200010];
std::vector<long long> v1;

int main() {
	FFT<long long> fft;
	int n, max1 = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		check[a] = true;
		max1 = std::max(max1, a);
	}
	check[0] = true;

	for (int i = 0; i <= 200000; i++) {
		if (check[i] == false)
			v1.push_back(0);
		else
			v1.push_back(1);
	}

	std::vector<long long> result = fft.multiply(v1, v1);

	int r = 0, m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		int a;
		scanf("%d", &a);

		if (a < result.size() && result[a] != 0)
			r++;
	}

	printf("%d\n", r);
}
