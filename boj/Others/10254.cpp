#include <stdio.h>
#include <algorithm>
#include <climits>
#include <vector>

struct point {
	long long x, y;
};

point input[200010];

long long ccw(point a, point b, point c) {
	return (long long)a.x * b.y + (long long)b.x * c.y + (long long)c.x * a.y - (long long)b.x * a.y - (long long)c.x * b.y - (long long)a.x * c.y;
}

long long dist(point a, point b) {
	long long gapx = a.x - b.x, gapy = a.y - b.y;
	return gapx * gapx + gapy * gapy;
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n, index = 1;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++) {
			scanf("%lld %lld", &input[i].x, &input[i].y);
			if (input[index].x > input[i].x) {
				index = i;
			}
			else if (input[index].x == input[i].x && input[index].y > input[i].y) {
				index = i;
			}
		}

		if (n == 2) {
			printf("%lld %lld %lld %lld\n", input[1].x, input[1].y, input[2].x, input[2].y);
			continue;
		}

		std::swap(input[1], input[index]);

		std::sort(input + 2, input + 1 + n, [&](point a, point b) {
			long long tmp = ccw(input[1], a, b);
			if (tmp == 0)
				return dist(input[1], a) < dist(input[1], b);
			return 0 > tmp;
		});

		std::vector<point> sk;

		sk.push_back(input[1]);
		for (int i = 2; i <= n; i++) {
			while (sk.size() > 1) {
				if (ccw(sk[sk.size() - 1], sk[sk.size() - 2], input[i]) <= 0)
					sk.pop_back();
				else
					break;
			}

			sk.push_back(input[i]);
		}

		while (sk.size() > 1) {
			if (ccw(sk[sk.size() - 1], sk[sk.size() - 2], input[1]) <= 0)
				sk.pop_back();
			else
				break;
		}

		if (sk.size() == 1) {
			printf("%lld %lld %lld %lld\n", input[1].x, input[1].y, input[n].x, input[n].y);
			continue;
		}

		int cur = 1, index1, index2;
		long long result = -1;
		for (int i = 0; i < sk.size(); i++) {
			int ni = (i + 1) % sk.size();

			while (1) {
				int nc = (cur + 1) % sk.size();
				point n1, n2;
				n1.x = sk[ni].x - sk[i].x;
				n1.y = sk[ni].y - sk[i].y;
				n2.x = sk[nc].x - sk[cur].x;
				n2.y = sk[nc].y - sk[cur].y;

				if (ccw(point({ 0, 0 }), n1, n2) < 0) {
					cur = nc;
				}
				else
					break;
			}

			if (dist(sk[i], sk[cur]) > result) {
				result = dist(sk[i], sk[cur]);
				index1 = i;
				index2 = cur;
			}
		}

		printf("%lld %lld %lld %lld\n", sk[index1].x, sk[index1].y, sk[index2].x, sk[index2].y);
	}
}