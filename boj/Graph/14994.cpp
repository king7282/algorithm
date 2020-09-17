#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

struct info {
	int x, y;
	double weight;

	info(int x, int y, double weight) : x(x), y(y), weight(weight) {}
};

double input[510][510];
int tree[1010];
bool check[510];
std::vector<int> v[510];
std::vector<std::vector<int>> group;
std::vector<std::pair<int, int>> result;

int find(int num) {
	if (tree[num] == -1)
		return num;
	return tree[num] = find(tree[num]);
}

void un(int a, int b) {
	a = find(a), b = find(b);
	if (a != b)
		tree[a] = b;
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf("%lf", &input[i][j]);

	for (int i = 0; i < m; i++) {
		int k;
		scanf("%d", &k);

		for (int j = 0; j < k; j++) {
			int a;
			scanf("%d", &a);
			v[i].push_back(a);
		}

		std::sort(v[i].begin(), v[i].end());
	}

	for (int i = 0; i < m; i++) {
		if (check[i] == true)
			continue;

		group.push_back(std::vector<int>());
		group[group.size() - 1].push_back(i);

		for (int j = i + 1; j < m; j++) {
			if (check[j] == true || v[i].size() != v[j].size())
				continue;
			bool flag = true;
			for (int k = 0; k < v[i].size() && flag; k++) {
				if (v[i][k] != v[j][k])
					flag = false;
			}

			if (flag) {
				check[j] = true;
				group[group.size() - 1].push_back(j);
			}
		}
	}

	for (int i = 0; i < group.size(); i++) {
		memset(tree, -1, sizeof(tree));
		std::vector<info> edges;

		for (int j = 0; j < v[group[i][0]].size(); j++) {
			for (int k = 0; k < group[i].size(); k++) {
				edges.push_back(info(group[i][k], v[group[i][0]][j] + m, input[group[i][k]][v[group[i][0]][j]]));
			}
		}

		std::sort(edges.begin(), edges.end(), [](info a, info b) {
			return a.weight > b.weight;
		});

		for (int j = 0; j < edges.size(); j++) {
			if (find(edges[j].x) != find(edges[j].y)) {
				un(edges[j].x, edges[j].y);
				result.push_back(std::make_pair(edges[j].x, edges[j].y - m));
			}
		}
	}

	std::sort(result.begin(), result.end());
	for (int i = 0; i < result.size(); i++)
		printf("%d %d\n", result[i].first, result[i].second);
}