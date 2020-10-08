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

char input[100010], machine[100010], mov[3][2] = { {'R', 'P'}, {'S', 'R'}, {'P', 'S'} };
std::vector<long long> v1, v2;
long long result[1000010];

int main(void) {
	FFT<long long> fft;
	int n, m, limits = 0;
	scanf("%d %d", &n, &m);
	getchar();

	for (int i = 1; i <= n; i++)
		scanf("%c", input + i);
	getchar();

	for (int i = 1; i <= m; i++)
		scanf("%c", machine + i);
	
	for (int k = 0; k < 3; k++) {
		v1.clear(); v2.clear();

		for (int i = 1; i <= n; i++) {
			if (input[i] == mov[k][0])
				v1.push_back(1);
			else
				v1.push_back(0);
		}

		for (int i = 1; i <= m; i++) {
			if (machine[i] == mov[k][1])
				v2.push_back(1);
			else
				v2.push_back(0);
		}

		std::reverse(v2.begin(), v2.end());

		std::vector<long long> v = fft.multiply(v1, v2);

		limits = std::max(limits, (int)v.size());
		for (int i = m - 1; i < v.size(); i++)
			result[i] += v[i];
	}

	long long r = 0;
	for (int i = m - 1; i < limits; i++)
		r = std::max(r, result[i]);

	printf("%lld\n", r);
}