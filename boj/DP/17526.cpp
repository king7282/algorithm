#include <stdio.h>
#include <algorithm>
#include <climits>
#include <vector>

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
long long dp[10010], T[10010], F[10010];

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


long long space[100010], times[100010], paces[100010];

int main(void) {
	int n;
	scanf("%d", &n);
	
	for (int i = 1; i < n; i++) {
		long long a;
		scanf("%lld", &a);
		space[i + 1] = space[i] + a;
	}

	for (int i = 1; i < n; i++) {
		long long a, b;
		scanf("%lld %lld", &a, &b);

		times[i] = a;
		paces[i] = b;
	}

	nodeList.push_back({ -1, -1, {0, LLONG_MIN / 2}, 0, space[n] });
	insert(0, line(-1 * paces[1], (-1 * times[1] + space[1] * paces[1])));
	for (int i = 2; i < n; i++) {
		long long tmp = -1 * query(0, space[i]);
		insert(0, line(-1 * paces[i], (space[i] * paces[i] - tmp - times[i])));
	}

	printf("%lld\n", -1 * query(0, space[n]));

}