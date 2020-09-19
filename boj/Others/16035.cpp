#include <stdio.h>
#include <algorithm>
#include <cstring>

int tables[10][10], result;
std::pair<int, int> cnt[10];
int n, m;

void func(int num, int o) {
	if (n == num) {
		result++;
		return;
	}

	if (tables[num][o] != 0) {
		if (o < n)
			func(num, o + 1);
		else
			func(num + 1, num + 2);
	}
	else {
		cnt[num].first++;
		cnt[o].second++;

		if (cnt[num].first <= n / 2 && cnt[o].first <= n / 2 && cnt[num].second <= n / 2 && cnt[o].second <= n / 2) {
			if (o < n)
				func(num, o + 1);
			else
				func(num + 1, num + 2);
		}

		cnt[num].first--;
		cnt[o].second--;

		cnt[num].second++;
		cnt[o].first++;

		if (cnt[num].first <= n / 2 && cnt[o].first <= n / 2 && cnt[num].second <= n / 2 && cnt[o].second <= n / 2) {
			if (o < n)
				func(num, o + 1);
			else
				func(num + 1, num + 2);
		}

		cnt[num].second--;
		cnt[o].first--;

	}
}

int main(void) {
	while (1) {
		scanf("%d", &n);
		if (n == 0)
			break;

		scanf("%d", &m);
		memset(tables, 0, sizeof(tables));
		memset(cnt, 0, sizeof(cnt));
		result = 0;
		bool flag = false;
		for (int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);

			tables[a][b] = 1;
			tables[b][a] = -1;
			cnt[a].first++;
			cnt[b].second++;
			if (cnt[a].first > n / 2 || cnt[a].second > n / 2 || cnt[b].first > n / 2 || cnt[b].second > n / 2)
				flag = true;
		}

		if (flag) {
			printf("0\n");
			continue;
		}
		func(1, 2);
		printf("%d\n", result);
	}
}