#include <stdio.h>
#include <vector>
#include <algorithm>

struct info {
	long long x, y, z;
	info(long long x = 0, long long y = 0, long long z = 0) : x(x), y(y), z(z) {}
};

info input[110];

double func(const std::vector<info> &v) {
	long long xhap = 0, yhap = 0, zhap = 0;
	double result = 0;

	for (int i = 0; i < v.size(); i++) {
		xhap += v[i].x;
		yhap += v[i].y;
		zhap += v[i].z;
	}

	for (int i = 0; i < v.size(); i++) {
		double tmpx = v[i].x - (double)xhap / v.size(), tmpy = v[i].y - (double)yhap / v.size(), tmpz = v[i].z - (double)zhap / v.size();
		result += tmpx * tmpx + tmpy * tmpy + tmpz * tmpz;
	}
	return result;
}

long long ccw(info tmp1, info tmp2) {
	return tmp1.x * tmp2.x + tmp1.y * tmp2.y + tmp1.z * tmp2.z;
}

info external(info a, info b, info c) {
	info tmp1, tmp2;
	tmp1.x = b.x - a.x; tmp1.y = b.y - a.y; tmp1.z = b.z - a.z;
	tmp2.x = c.x - a.x; tmp2.y = c.y - a.y; tmp2.z = c.z - a.z;

	info result;
	result.x = tmp1.y * tmp2.z - tmp1.z * tmp2.y;
	result.y = tmp1.z * tmp2.x - tmp1.x * tmp2.z;
	result.z = tmp1.x * tmp2.y - tmp1.y * tmp2.x;

	return result;
}

int main(void) {
	int n, ss;
	scanf("%d %d", &n, &ss);

	for (int i = 1; i <= n; i++)
		scanf("%lld %lld %lld", &input[i].x, &input[i].y, &input[i].z);

	if (n == 1 || (n == 2 && ss == 2)) {
		printf("%lf\n", (double)0);
		return 0;
	}

	double result = -1;
	if (ss >= 1) {
		std::vector<info> v;

		for (int i = 1; i <= n; i++)
			v.push_back(input[i]);
		result = func(v);
	}
	if (ss >= 2) {
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				for (int k = j + 1; k <= n; k++) {
					std::vector<info> a, b;
					info ex = external(input[i], input[j], input[k]);

					for (int t = 1; t <= n; t++) {
						if (t == i || t == j || t == k)
							continue;
						info tmp;
						tmp.x = input[t].x - input[i].x;
						tmp.y = input[t].y - input[i].y;
						tmp.z = input[t].z - input[i].z;

						if (ccw(ex, tmp) < 0)
							a.push_back(input[t]);
						else
							b.push_back(input[t]);
					}

					std::vector<info> ttmp;
					ttmp.push_back(input[i]);
					ttmp.push_back(input[j]);
					ttmp.push_back(input[k]);

					a.push_back(ttmp[0]);
					a.push_back(ttmp[1]);
					a.push_back(ttmp[2]);
					result = std::min(result, func(a) + func(b));
					a.pop_back();
					a.pop_back();
					a.pop_back();

					a.push_back(ttmp[0]);
					a.push_back(ttmp[1]);
					b.push_back(ttmp[2]);
					result = std::min(result, func(a) + func(b));
					a.pop_back();
					a.pop_back();
					b.pop_back();

					a.push_back(ttmp[0]);
					b.push_back(ttmp[1]);
					a.push_back(ttmp[2]);
					result = std::min(result, func(a) + func(b));
					a.pop_back();
					b.pop_back();
					a.pop_back();

					b.push_back(ttmp[0]);
					a.push_back(ttmp[1]);
					a.push_back(ttmp[2]);
					result = std::min(result, func(a) + func(b));
					b.pop_back();
					a.pop_back();
					a.pop_back();

					a.push_back(ttmp[0]);
					b.push_back(ttmp[1]);
					b.push_back(ttmp[2]);
					result = std::min(result, func(a) + func(b));
					a.pop_back();
					b.pop_back();
					b.pop_back();

					b.push_back(ttmp[0]);
					a.push_back(ttmp[1]);
					b.push_back(ttmp[2]);
					result = std::min(result, func(a) + func(b));
					b.pop_back();
					a.pop_back();
					b.pop_back();

					b.push_back(ttmp[0]);
					b.push_back(ttmp[1]);
					a.push_back(ttmp[2]);
					result = std::min(result, func(a) + func(b));
					b.pop_back();
					b.pop_back();
					a.pop_back();


					b.push_back(ttmp[0]);
					b.push_back(ttmp[1]);
					b.push_back(ttmp[2]);
					result = std::min(result, func(a) + func(b));
					b.pop_back();
					b.pop_back();
					b.pop_back();
				}
			}
		}

	}

	long long qas = result * 10000000;
	if (qas % 10 >= 5)
		result += 0.0000001;
	printf("%.6lf\n", result);
}