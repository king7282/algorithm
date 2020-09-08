#include <stdio.h>

int result[10010];

int main(void) {
	int n;
	scanf("%d", &n);

	int cur = 1;
	for (int i = 2; i <= n; i++) {
		int v1, v2;
		printf("? %d %d\n", cur, i);
		fflush(stdout);
		scanf("%d", &v1);
		printf("? %d %d\n", i, cur);
		fflush(stdout);
		scanf("%d", &v2);

		if (v1 < v2) {
			result[i] = v2;
		}
		else {
			result[cur] = v1;
			cur = i;
		}
	}
	result[cur] = n;

	printf("! ");
	for (int i = 1; i <= n; i++)
		printf("%d ", result[i]);
	printf("\n");
}