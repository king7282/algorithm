#include <string>
#include <iostream>
#include <stdio.h>
#include <complex>
#include <vector>
#include <algorithm>

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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	FFT<int> fft;
	std::vector<int> a, b;
	std::string input1, input2;
	std::cin >> input1 >> input2;

	for (int i = 0; i < input1.size(); i++)
		a.push_back(input1[i] - '0');

	for (int i = 0; i < input2.size(); i++)
		b.push_back(input2[i] - '0');

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	for (int i = 0; i < input1.size(); i++)a.push_back(0);
	for (int i = 0; i < input2.size(); i++)b.push_back(0);

	a = fft.multiply(a, b);

	for (int i = 0; i < a.size() - 1; i++) {
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}

	if (a.back() >= 10) {
		a.push_back(a.back() / 10);
		a[a.size() - 2] %= 10;
	}

	bool flag = false;
	for (int i = a.size() - 1; i >= 0; i--) {
		if (!flag && a[i] == 0)
			continue;
		flag = true;
		printf("%d", a[i]);
	}

	if (!flag)
		printf("0");
}
