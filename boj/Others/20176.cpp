#include <stdio.h>
#include <algorithm>
#include <vector>
#include <complex>
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

bool input1[60001], input2[60001], input3[60001];

int main(void) {
	int n1, n2, n3;

	scanf("%d", &n1);

	for (int i = 1; i <= n1; i++) {
		int a;
		scanf("%d", &a);
		input1[a + 30000] = true;
	}

	scanf("%d", &n2);

	for (int i = 1; i <= n2; i++) {
		int a;
		scanf("%d", &a);
		input2[a + 30000] = true;
	}

	scanf("%d", &n3);

	for (int i = 1; i <= n3; i++) {
		int a;
		scanf("%d", &a);
		input3[a + 30000] = true;
	}

	std::vector<int> first_odd, first_even, second;

	for (int i = 0; i <= 60000; i++) {
		if (i % 2 == 0)
			first_even.push_back(input1[i]);
		else
			first_odd.push_back(input1[i]);

		second.push_back(input2[i]);
	}

	std::reverse(first_even.begin(), first_even.end());
	std::reverse(first_odd.begin(), first_odd.end());

	FFT<int> fft;

	std::vector<int> even = fft.multiply(first_even, second), odd = fft.multiply(first_odd, second);

	long long result = 0;
	int cur = -30000 - (29999 + 30000);
	for (int i = 0; i < odd.size(); i++) {
		if (cur + 30000 >= 0 && cur + 30000 <= 60000 && input3[cur + 30000] == true)
			result += odd[i];
		cur += 2;
	}

	cur = -30000 - (30000 + 30000);
	for (int i = 0; i < even.size(); i++) {
		if (cur + 30000 >= 0 && cur + 30000 <= 60000 && input3[cur + 30000] == true)
			result += even[i];
		cur += 2;
	}

	printf("%lld\n", result);
}