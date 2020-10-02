#include <stdio.h>

int cur[110];

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);
	bool result = true;
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		if (!result)
			continue;

		bool flag = false;
		for (int i = 1; i <= k && !flag; i++) {
			if (cur[i] < a) {
				cur[i] = a;
				flag = true;
			}
		}

		if (!flag) {
			result = false;
		}
	}

	if (result) {
		printf("YES\n");
	}
	else
		printf("NO\n");
}