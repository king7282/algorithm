#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#define MOD 1000000000000000000LL;

struct info {
	int x, y, up, bitmask;
	info(int x = 0, int y = 0, int up = 0, int bitmask = 0) : x(x), y(y), up(up), bitmask(bitmask) {}
};

bool operator<(const info &a, const info &b) {
	if (a.bitmask == b.bitmask) {
		if (a.x == b.x) {
			if (a.y == b.y)
				return a.up < b.up;
			return a.y < b.y;
		}
		return a.x < b.x;
	}
	return a.bitmask < b.bitmask;
}

std::map<info, long long> dp;
int a, b, c;

long long func(int x, int y, int up, int bitmask) {
	if (x == a)
		return 1;

	if (dp.find(info(x, y, up, bitmask)) != dp.end())
		return dp[info(x, y, up, bitmask)];

	long long &r = dp[info(x, y, up, bitmask)];
	r = 0;

	int tmp = 1;
	for (int i = 0; i < y; i++)
		tmp *= (c + 1);
	int cur = (bitmask / tmp) % (c + 1);

	for (int i = 0; i <= std::min(cur, up); i++) {
		if (y + 1 == b) {
			r = (r + func(x + 1, 0, c, bitmask - cur * tmp + i * tmp)) % MOD;
		}
		else {
			r = (r + func(x, y + 1, i, bitmask - cur * tmp + i * tmp)) % MOD;
		}
	}
	return r;
}

int main(void) {
	scanf("%d %d %d", &a, &b, &c);
	int start = 0;
	for (int i = 0; i < b; i++) {
		start = start * (c + 1) + c;
	}

	printf("%lld\n", func(0, 0, c, start));
}
