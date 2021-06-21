#include <stdio.h>
#include <vector>

std::vector<int> group[100010];
int last[100010], result[100010], tmp[100010];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int k;
		scanf("%d", &k);

		for (int j = 1; j <= k; j++) {
			int a;
			scanf("%d", &a);
			group[i].push_back(a);
		}
	}

	for (int i = 1; i <= n; i++) {
		scanf("%d", last + i);
		tmp[i] = last[i];
	}

	for (int i = m; i >= 1; i--) {
		bool flag = false;

		for (int j = 0; j < group[i].size() && !flag; j++) {
			if (tmp[group[i][j]] == 0)
				flag = true;
		}

		if (flag) {
			for (int j = 0; j < group[i].size(); j++)
				tmp[group[i][j]] = 0;
		}
	}

	for (int i = 1; i <= n; i++) {
		result[i] = tmp[i];
	}

	for (int i = 1; i <= m; i++) {
		bool flag = false;

		for (int j = 0; j < group[i].size() && !flag; j++) {
			if (tmp[group[i][j]] == 1)
				flag = true;
		}

		if (flag) {
			for (int j = 0; j < group[i].size(); j++)
				tmp[group[i][j]] = 1;
		}
	}

	bool flag = true;
	for (int i = 1; i <= n && flag; i++) {
		if (tmp[i] != last[i])
			flag = false;
	}

	if (!flag) {
		printf("NO\n");
	}
	else {
		printf("YES\n");
		for (int i = 1; i <= n; i++)
			printf("%d ", result[i]);
	}

}