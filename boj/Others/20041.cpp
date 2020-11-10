#include <stdio.h>
#include <algorithm>

std::pair<int, int> caps[500010];
int n;

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d %d", &caps[i].first, &caps[i].second);

	std::pair<int, int> thief;
	scanf("%d %d", &thief.first, &thief.second);

	bool flag = true;
	for (int i = 1; i <= n && flag; i++) {
		if (caps[i].first >= thief.first) {
			if (caps[i].first - thief.first >= aabs(caps[i].second - thief.second))
				flag = false;
		}
	}

	if (flag) {
		printf("YES");
		return 0;
	}

	flag = true;
	for (int i = 1; i <= n && flag; i++) {
		if (caps[i].first <= thief.first) {
			if (aabs(caps[i].first - thief.first) >= aabs(caps[i].second - thief.second))
				flag = false;
		}
	}

	if (flag) {
		printf("YES");
		return 0;
	}

	flag = true;
	for (int i = 1; i <= n && flag; i++) {
		if (caps[i].second >= thief.second) {
			if (caps[i].second - thief.second >= aabs(caps[i].first - thief.first))
				flag = false;
		}
	}

	if (flag) {
		printf("YES");
		return 0;
	}

	flag = true;
	for (int i = 1; i <= n && flag; i++) {
		if (caps[i].second <= thief.second) {
			if (aabs(caps[i].second - thief.second) >= aabs(caps[i].first - thief.first))
				flag = false;
		}
	}

	if (flag) {
		printf("YES");
		return 0;
	}
	printf("NO\n");
}