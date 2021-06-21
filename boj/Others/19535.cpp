#include <stdio.h>
#include <vector>

std::vector<int> graph[300010];
long long n, G, D;
long long p[300010], children[300010][4];

void make_children(int cur, int parent) {
	p[cur] = parent;
	children[cur][0] = 1;
	for (int i = 0; i < graph[cur].size(); i++) {
		if (parent == graph[cur][i])
			continue;

		make_children(graph[cur][i], cur);
		children[cur][1] += children[graph[cur][i]][0];
		children[cur][2] += children[graph[cur][i]][1];
		children[cur][3] += children[graph[cur][i]][2];
	}
}

int main(void) {
	scanf("%lld", &n);

	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	for (int i = 1; i <= n; i++) {
		if (graph[i].size() < 3)
			continue;
		long long d = graph[i].size();
		G += d * (d - 1) * (d - 2) / 6;
	}

	make_children(1, 0);
	for (int i = 1; i <= n; i++) {
		D += children[i][3];
		if (p[i] != 0) {
			D += children[p[i]][2] - children[i][1];
		}
		if (p[p[i]] != 0) {
			D += children[p[p[i]]][1] - 1;
		}
		if (p[p[p[i]]] != 0) {
			D += 1;
		}
	}
	
	D /= 2;
	if (D > G * 3) {
		printf("D\n");
	}
	else if (D < G * 3) {
		printf("G\n");
	}
	else {
		printf("DUDUDUNGA\n");
	}
}