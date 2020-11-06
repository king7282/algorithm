#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

int degree[10010], next[10010];
std::vector<int> graph[10010], rev[10010], ori[10010], set[10010];
int check[10010], order[10010], cnt, scc[10010];
int result[10010];
std::pair<int, int> P[10010];

void dfs(int num) {
	check[num] = true;
	for (int i = 0; i < graph[num].size(); i++)
		if (check[graph[num][i]] == false)
			dfs(graph[num][i]);

	order[cnt++] = num;
}

void rev_dfs(int num) {
	scc[num] = cnt;
	set[cnt].push_back(num);

	for (int i = 0; i < rev[num].size(); i++)
		if (scc[rev[num][i]] == 0)
			rev_dfs(rev[num][i]);
}

int main(void) {
	int k, n;
	scanf("%d %d", &k, &n);

	for (int i = 1; i <= n; i++) {
		int a, b, c;
		char a1, b1, c1;
		scanf("%d %c %d %c %d %c", &a, &a1, &b, &b1, &c, &c1);
		
		a--; b--; c--;
		int ca = 2 * a, na = 2 * a + 1, cb = 2 * b, nb = 2 * b + 1, cc = 2 * c, nc = 2 * c + 1;
		if (a1 == 'B')
			std::swap(ca, na);
		if (b1 == 'B')
			std::swap(cb, nb);
		if (c1 == 'B')
			std::swap(cc, nc);

		graph[ca].push_back(nb);
		rev[nb].push_back(ca);
		graph[cb].push_back(na);
		rev[na].push_back(cb);

		graph[ca].push_back(nc);
		rev[nc].push_back(ca);
		graph[cc].push_back(na);
		rev[na].push_back(cc);

		graph[cb].push_back(nc);
		rev[nc].push_back(cb);
		graph[cc].push_back(nb);
		rev[nb].push_back(cc);
	}

	cnt = 0;
	for (int i = 0; i < 2 * k; i++) {
		if (check[i] == false) {
			dfs(i);
		}
	}

	cnt = 0;
	for (int i = 2 * k - 1; i >= 0; i--) {
		if (scc[order[i]] == 0) {
			cnt++;
			rev_dfs(order[i]);
		}
	}

	bool flag = true;
	for (int i = 0; i < k && flag; i++) {
		if (scc[i * 2] == scc[i * 2 + 1])
			flag = false;
	}

	if (!flag)
		printf("-1\n");
	else {
		memset(result, -1, sizeof(result));
		for (int i = 0; i < k * 2; i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				if (scc[i] != scc[graph[i][j]]) {
					ori[scc[i]].push_back(scc[graph[i][j]]);
					degree[scc[graph[i][j]]]++;
				}
			}
		}
		
		std::queue<int> qu;
		for (int i = 1; i <= cnt; i++)
			if (degree[i] == 0)
				qu.push(i);

		while (!qu.empty()) {
			int front = qu.front();
			qu.pop();

			for (int i = 0; i < set[front].size(); i++) {
				result[set[front][i] / 2] = set[front][i] % 2;
			}

			for (int i = 0; i < ori[front].size(); i++) {
				degree[ori[front][i]]--;
				if (degree[ori[front][i]] == 0)
					qu.push(ori[front][i]);
			}
		}

		for (int i = 0; i < k; i++) {
			if (result[i] == 1)
				printf("R");
			else
				printf("B");
		}
		printf("\n");
	}


}