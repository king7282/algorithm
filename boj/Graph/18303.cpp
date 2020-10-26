#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>

bool check[100010];
bool direct[100010], result[100010];
std::vector<int> ori[100010], rev[100010], set[100010], graph[100010], reverse[100010];
int cnt, order[100010], scc[100010], tmp, ssize[100010];

void dfs(int num) {
	check[num] = true;
	for (int i = 0; i < ori[num].size(); i++)
		if (check[ori[num][i]] == false)
			dfs(ori[num][i]);

	order[cnt++] = num;
}

void rev_dfs(int num) {
	if (direct[num] == true)
		tmp++;

	scc[num] = cnt;
	set[cnt].push_back(num);

	for (int i = 0; i < rev[num].size(); i++)
		if (scc[rev[num][i]] == 0)
			rev_dfs(rev[num][i]);
}

int main(void) {
	int n, m, t;
	scanf("%d %d %d", &n, &m, &t);

	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		if (b == t)
			direct[a] = true;
		else {
			if (a != t) {
				ori[a].push_back(b);
				rev[b].push_back(a);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (check[i] == false) {
			dfs(i);
		}
	}

	cnt = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (scc[order[i]] == 0) {
			tmp = 0;
			cnt++;
			rev_dfs(order[i]);
			if (tmp >= 2)
				result[cnt] = true;
		}
	}

	for (int i = 0; i < n; i++) {
		if (scc[i] == 0)
			continue;

		for (int j = 0; j < ori[i].size(); j++) {
			if (scc[ori[i][j]] != 0 && scc[ori[i][j]] != scc[i]) {
				graph[scc[i]].push_back(scc[ori[i][j]]);
				reverse[scc[ori[i][j]]].push_back(scc[i]);
			}
		}
	}

	std::queue<int> qu;
	for (int i = 1; i <= cnt; i++) {
		ssize[i] = graph[i].size();
		if (graph[i].size() == 0)
			qu.push(i);
	}

	memset(check, false, sizeof(check));
	while (!qu.empty()) {
		int front = qu.front();
		qu.pop();
		bool flag = false;

		for (int i = 0; i < graph[front].size(); i++) {
			if (check[graph[front][i]] == true)
				flag = true;
		}

		if (flag)
			check[front] = result[front] = true;

		for (int i = 0; i < set[front].size() && !flag; i++)
			if (direct[set[front][i]] == true)
				flag = true;

		if (flag)
			check[front] = true;

		for (int i = 0; i < reverse[front].size(); i++) {
			ssize[reverse[front][i]]--;
			if (ssize[reverse[front][i]] == 0)
				qu.push(reverse[front][i]);
		}
	}

	for (int i = 1; i <= cnt; i++) {
		if (result[i] == true) {
			for (int j = 0; j < set[i].size(); j++) {
				direct[set[i][j]] = false;
			}
		}
	}

	std::vector<int> tttmp;
	for (int i = 0; i < n; i++) {
		if (direct[i] == true)
			tttmp.push_back(i);
	}

	std::sort(tttmp.begin(), tttmp.end());
	printf("%d\n", tttmp.size());
	for (int i = 0; i < tttmp.size(); i++)
		printf("%d\n", tttmp[i]);
}