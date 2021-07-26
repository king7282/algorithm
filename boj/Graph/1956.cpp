#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <climits>

long long graph[410][410];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	
	memset(graph, -1, sizeof(graph));
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		graph[a][b] = c;
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (graph[i][k] != -1 && graph[k][j] != -1) {
					if (graph[i][j] == -1)
						graph[i][j] = graph[i][k] + graph[k][j];
					else
						graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
				}
			}
		}
	}

	long long result = LLONG_MAX / 2;
	for (int i = 1; i <= n; i++) {
		if (graph[i][i] == -1)
			continue;
		result = std::min(result, graph[i][i]);
	}

	if (result == LLONG_MAX / 2)
		printf("-1\n");
	else
		printf("%lld\n", result);
}