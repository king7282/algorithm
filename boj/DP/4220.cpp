#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>
#include <assert.h>

struct info {
	long long day, cost, resale, profit;
	info(long long day = 0, long long cost = 0, long long resale = 0, long long profit = 0) : day(day), cost(cost), resale(resale), profit(profit) {}
};

struct line {
	long long a, b;
	line(long long a, long long b) : a(a), b(b) {}
};

struct node {
	int nLeft, nRight;
	line L;
	long long xLeft, xRight;
};

std::vector<node> nodeList;

long long getPoint(line l, long long x) {
	return l.a * x + l.b;
}

void insert(int index, line val) {
	long long mid = (nodeList[index].xLeft + nodeList[index].xRight) / 2;
	line low = nodeList[index].L, high = val;

	if (getPoint(low, nodeList[index].xLeft) >= getPoint(high, nodeList[index].xLeft))
		std::swap(low, high);

	if (getPoint(low, nodeList[index].xRight) <= getPoint(high, nodeList[index].xRight)) {
		nodeList[index].L = high;
	}
	else {
		if (getPoint(low, mid) >= getPoint(high, mid)) {
			nodeList[index].L = low;
			if (nodeList[index].nLeft == -1) {
				nodeList[index].nLeft = nodeList.size();
				nodeList.push_back({ -1, -1, {0, LLONG_MIN / 2}, nodeList[index].xLeft, mid });
			}
			insert(nodeList[index].nLeft, high);
		}
		else {
			nodeList[index].L = high;
			if (nodeList[index].nRight == -1) {
				nodeList[index].nRight = nodeList.size();
				nodeList.push_back({ -1, -1, {0, LLONG_MIN / 2}, mid + 1, nodeList[index].xRight });
			}
			insert(nodeList[index].nRight, low);
		}
	}
}

long long query(int index, long long x) {
	if (index == -1)
		return LLONG_MIN / 2;

	long long mid = (nodeList[index].xLeft + nodeList[index].xRight) / 2;
	if (mid <= x) {
		return std::max(getPoint(nodeList[index].L, x), query(nodeList[index].nRight, x));
	}
	else
		return std::max(getPoint(nodeList[index].L, x), query(nodeList[index].nLeft, x));
}

info input[100010];

int main(void) {
	int test = 0;
	while (1) {
		int n;
		long long c, d;
		scanf("%d %lld %lld", &n, &c, &d);
		if (n == 0 && c == 0 && d == 0)
			break;
		assert(1 <= n && n <= 100000);
		assert(1 <= c && c <= 1000000000);
		assert(1 <= d && d <= 1000000000);

		test++;
		for (int i = 1; i <= n; i++) {
			scanf("%lld %lld %lld %lld", &input[i].day, &input[i].cost, &input[i].resale, &input[i].profit);
			assert(1 <= input[i].day && input[i].day <= d);
		}

		std::sort(input + 1, input + 1 + n, [](info a, info b) {
			return a.day < b.day;
			});

		nodeList.push_back({ -1, -1, {0, LLONG_MIN / 2}, 0, d + 1 });
		insert(0, line(0, c));

		for (int i = 1; i <= n; i++) {
			long long tmp = query(0, input[i].day);
			if (tmp >= input[i].cost)
				insert(0, line(input[i].profit, tmp + input[i].resale - (input[i].day + 1) * input[i].profit - input[i].cost));
		}

		printf("Case %d: %lld\n", test, query(0, d + 1));
		nodeList.clear();
		memset(input, 0, sizeof(input));
	}
}