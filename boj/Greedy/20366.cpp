#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

struct info {
	int value, x, y;
	info(int value, int x, int y) : value(value), x(x), y(y) {}
};

int input[610];
std::vector<info> X;

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

int main(void) {
	int n;
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++)
		scanf("%d", input + i);

	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			X.push_back(info(input[i] + input[j], i, j));
		}
	}

	std::sort(X.begin(), X.end(), [](info a, info b) {
		return a.value < b.value;
	});

	int result = INT_MAX / 2;

	for (int i = 0; i < X.size(); i++) {

		for (int prev = i; prev >= std::max(0, i - 4); prev--) {
			if (X[i].x != X[prev].x && X[i].x != X[prev].y && X[i].y != X[prev].x && X[i].y != X[prev].y)
				result = std::min(result, aabs(X[i].value - X[prev].value));
		}

		for (int next = i; next <= std::min((int)X.size() - 1, i + 4); next++) {
			if (X[i].x != X[next].x && X[i].x != X[next].y && X[i].y != X[next].x && X[i].y != X[next].y)
				result = std::min(result, aabs(X[i].value - X[next].value));
		}
	}

	printf("%d\n", result);
}