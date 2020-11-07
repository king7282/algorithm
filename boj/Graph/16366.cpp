#include <stdio.h>
#include <algorithm>
#include <vector>

struct info {
	int next, value;
	info(int next, int value) : next(next), value(value) {}
};

bool tmp[1010];
bool check[1010][1010];
std::vector<int> human, alien, base;
std::vector<info> graph[1010];

void func(int n1, int n2) {
	check[n1][n2] = true;
	for (int i = 0; i < graph[n1].size(); i++) {
		for (int j = 0; j < graph[n2].size(); j++) {
			if (graph[n1][i].value == graph[n2][j].value) {
				if (check[graph[n1][i].next][graph[n2][j].next] == false)
					func(graph[n1][i].next, graph[n2][j].next);
			}
		}
	}
}

int main(void) {
	int n, w, c, h, m;
	scanf("%d %d %d %d %d", &n, &w, &c, &h, &m);

	for (int i = 1; i <= h; i++) {
		int a;
		scanf("%d", &a);
		human.push_back(a);
		tmp[a] = true;
	}

	for (int i = 0; i < n; i++) {
		if (tmp[i] == false)
			alien.push_back(i);
	}

	for (int i = 1; i <= m; i++) {
		int a;
		scanf("%d", &a);
		base.push_back(a);
	}
	
	for (int i = 1; i <= w; i++) {
		int x, y, value;
		scanf("%d %d %d", &x, &value, &y);
		graph[x].push_back(info(y, value));
	}
	
	for (int i = 0; i < human.size(); i++) {
		for (int j = 0; j < alien.size(); j++) {
			if (check[human[i]][alien[j]] == false) {
				func(human[i], alien[j]);
			}
		}
	}

	bool result = false;
	for (int i = 0; i < base.size() && !result; i++) {
		for (int j = 0; j < base.size() && !result; j++) {
			if (check[base[i]][base[j]] == true)
				result = true;
		}
	}

	if (result)
		printf("YES\n");
	else
		printf("NO\n");
}