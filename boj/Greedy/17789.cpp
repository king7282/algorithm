#include <stdio.h>
#include <algorithm>
#include <cstring>

struct info {
	int x, y, index;
};

struct node {
	int value, index;
};

info vase[10010];
node p[10010];
int result[10010];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	memset(result, -1, sizeof(result));

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &vase[i].x, &vase[i].y);
		if (vase[i].x > vase[i].y)
			std::swap(vase[i].x, vase[i].y);
		vase[i].index = i;
	}

	for (int i = 1; i <= m; i++) {
		scanf("%d", &p[i].value);
		p[i].index = i;
	}

	std::sort(vase + 1, vase + 1 + n, [](info a, info b) {
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	});

	std::sort(p + 1, p + 1 + m, [](node a, node b) {
		return a.value < b.value;
	});

	bool flag = false;
	int prev = 1;
	for (int i = 1; i <= m; i++) {
		while (prev <= n && !(vase[prev].x <= p[i].value && p[i].value <= vase[prev].y))
			prev++;
		if (prev > n) {
			flag = true;
			break;
		}
		result[p[i].index] = vase[prev].index;
		prev++;
	}

	if (flag) {
		printf("impossible\n");
	}
	else {
		for (int i = 1; i <= m; i++)
			printf("%d\n", result[i]);
	}
}