#include <stdio.h>
#include <algorithm>

int weight[110][110];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if (weight[a][b] == 0)
			weight[a][b] = c;
		else
			weight[a][b] = std::min(weight[a][b], c);
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (weight[i][k] == 0 || weight[k][j] == 0)
					continue;

				if (weight[i][j] == 0)
					weight[i][j] = weight[i][k] + weight[k][j];
				else
					weight[i][j] = std::min(weight[i][j], weight[i][k] + weight[k][j]);
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j)
				printf("0 ");
			else
				printf("%d ", weight[i][j]);
		}
		printf("\n");
	}
}