#include <stdio.h>

int graph[510][510];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		
		graph[a][b] = 1;
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (graph[i][k] == 1 && graph[k][j] == 1)
					graph[i][j] = 1;
			}
		}
	}

	int result = 0;
	for (int i = 1; i <= n; i++) {
		bool flag = true;

		for (int j = 1; j <= n && flag; j++) {
			if (i == j)
				continue;

			if (graph[i][j] == 0 && graph[j][i] == 0)
				flag = false;
		}

		if (flag)
			result++;
	}

	printf("%d\n", result);
}