#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>

struct node {
	int x, y, weight;
	node(int x, int y, int weight) : x(x), y(y), weight(weight) {}
};

struct info {
	int up, down, left, right;
};

std::pair<int, int> input[1010];
std::vector<node> graph;
std::vector<std::pair<int, int>> points, pointX[1010], pointY[1010];
std::pair<int, int> direction[1000010][4];
int tree[1010], n;

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

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

bool OK(int num) {
	memset(tree, -1, sizeof(tree));

	for (int i = 0; i < graph.size() && graph[i].weight <= num; i++) {
		un(graph[i].x, graph[i].y);
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (find(i) == i)
			cnt++;
	}

	if (cnt == 1)
		return true;
	if (cnt > 4)
		return false;

	for (int i = 0; i < points.size(); i++) {
		std::vector<int> tmp;
		for (int j = 0; j < 4; j++)
			if (direction[i][j].second != 0 && direction[i][j].first <= num)
				tmp.push_back(find(direction[i][j].second));

		std::sort(tmp.begin(), tmp.end());
		tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
		if (tmp.size() == cnt)
			return true;
	}

	return false;
}

int main(void) {
	scanf("%d", &n);

	std::vector<int> X, Y;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &input[i].first, &input[i].second);

		for (int j = 1; j < i; j++) {
			if (input[i].first == input[j].first) {
				graph.push_back(node(i, j, aabs(input[i].second - input[j].second)));
				points.push_back(std::make_pair(input[i].first, (input[j].second + input[i].second) / 2));
			}
			else if (input[i].second == input[j].second) {
				graph.push_back(node(i, j, aabs(input[i].first - input[j].first)));
				points.push_back(std::make_pair((input[i].first + input[j].first) / 2, input[i].second));
			}
			else {
				points.push_back(std::make_pair(input[i].first, input[j].second));
				points.push_back(std::make_pair(input[j].first, input[i].second));
			}
		}
		X.push_back(input[i].first);
		Y.push_back(input[i].second);
	}

	std::sort(graph.begin(), graph.end(), [](node a, node b) {
		return a.weight < b.weight;
	});

	std::sort(X.begin(), X.end());
	std::sort(Y.begin(), Y.end());
	std::sort(points.begin(), points.end());

	X.erase(std::unique(X.begin(), X.end()), X.end());
	Y.erase(std::unique(Y.begin(), Y.end()), Y.end());
	points.erase(std::unique(points.begin(), points.end()), points.end());


	for (int i = 1; i <= n; i++) {
		int index1 = std::lower_bound(X.begin(), X.end(), input[i].first) - X.begin(), index2 = std::lower_bound(Y.begin(), Y.end(), input[i].second) - Y.begin();
		pointX[index1].push_back(std::make_pair(input[i].second, i));
		pointY[index2].push_back(std::make_pair(input[i].first, i));
	}

	for (int i = 0; i < X.size(); i++)
		std::sort(pointX[i].begin(), pointX[i].end());

	for (int i = 0; i < Y.size(); i++)
		std::sort(pointY[i].begin(), pointY[i].end());

	for (int i = 0; i < points.size(); i++) {
		int index1 = std::lower_bound(X.begin(), X.end(), points[i].first) - X.begin(), index2 = std::lower_bound(Y.begin(), Y.end(), points[i].second) - Y.begin();
		if (X[index1] == points[i].first) {
			int index = std::lower_bound(pointX[index1].begin(), pointX[index1].end(), std::make_pair(points[i].second, 0)) - pointX[index1].begin();
			if (index != 0) {
				direction[i][0] = std::make_pair(aabs(points[i].second - pointX[index1][index - 1].first), pointX[index1][index - 1].second);
			}
			if (index != pointX[index1].size()) {
				direction[i][1] = std::make_pair(aabs(points[i].second - pointX[index1][index].first), pointX[index1][index].second);
			}
		}

		if (Y[index2] == points[i].second) {
			int index = std::lower_bound(pointY[index2].begin(), pointY[index2].end(), std::make_pair(points[i].first, 0)) - pointY[index2].begin();

			if (index != 0) {
				direction[i][2] = std::make_pair(aabs(points[i].first - pointY[index2][index - 1].first), pointY[index2][index - 1].second);
			}

			if (index != pointY[index2].size()) {
				direction[i][3] = std::make_pair(aabs(points[i].first - pointY[index2][index].first), pointY[index2][index].second);
			}
		}
	}

	long long s = 1, e = 2000000000, r = 2000000001;

	while (s <= e) {
		long long mid = (s + e) / 2;

		if (OK(mid)) {
			e = mid - 1;
			r = std::min(r, mid);
		}
		else
			s = mid + 1;
	}

	if (r == 2000000001)
		printf("-1\n");
	else
		printf("%I64d\n", r);
}