#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>
#include <set>
#include <climits>
#define SIZE 131072

struct info {
	int x, y, z;
	info(int x, int y, int z) : x(x), y(y), z(z) {}
};

std::pair<long long, int> tree[SIZE * 2 + 1];

void update(int num, std::pair<long long, int> val) {
	num |= SIZE;
	tree[num] = val;

	while (num >>= 1)
		tree[num] = std::min(tree[num << 1], tree[num << 1 | 1]);
}

std::pair<long long, int> query(int s, int e) {
	s |= SIZE, e |= SIZE;
	std::pair<long long, int> r = std::make_pair(LLONG_MAX / 2, INT_MAX / 2);

	while (s <= e) {
		if (s % 2 == 1) r = std::min(r, tree[s]);
		if (e % 2 == 0) r = std::min(r, tree[e]);
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}

	return r;
}

long long visited[51][51][51];
std::vector<std::pair<int, long long>> graph[4][51];
int goals[4] = { 0, 1, 1, 1 }, cnt1, cnt2, f1 = 1, f2 = 1;

int change_value(info value) {
	return (value.x - 1) * 50 * 50 + (value.y - 1) * 50 + (value.z - 1);
}

info change_info(int value) {
	info result(0, 0, 0);

	result.z = value % 50 + 1;
	value /= 50;
	result.y = value % 50 + 1;
	value /= 50;
	result.x = value + 1;

	return result;
}

int main(void) {
	int p;
	scanf("%d", &p);

	for (int t = 1; t <= p; t++) {
		int n, m;
		scanf("%d %d", &n, &m);
		f1 *= n;
		f2 *= n + m;
		for (int i = 1; i <= n; i++) {
			long long h;
			scanf("%lld", &h);
			graph[t][i].push_back(std::make_pair(i, h));
		}

		for (int i = 1; i <= m; i++) {
			int x, y;
			long long h;
			scanf("%d %d %lld", &x, &y, &h);
			graph[t][x].push_back(std::make_pair(y, h));
		}
		scanf("%d", goals + t);
	}

	if (p <= 2)
		graph[3][1].push_back(std::make_pair(1, 0));
	if (p == 1)
		graph[2][1].push_back(std::make_pair(1, 0));

	for (int i = 0; i < 50 * 50 * 50; i++) {
		update(i, std::make_pair(LLONG_MAX / 2, i));
	}

	int start = 0, finish = 50 * 50 * 50 - 1;
	memset(visited, 0x7f, sizeof(visited));
	visited[1][1][1] = 0;
	update(change_value(info(1, 1, 1)), std::make_pair(0, change_value(info(1, 1, 1))));

	while (1) {
		std::pair<long long, int> tmp = query(start, finish);
		if (tmp.first == LLONG_MAX / 2)
			break;

		cnt1++;
		update(tmp.second, std::make_pair(LLONG_MAX / 2, tmp.second));
		info top = change_info(tmp.second);

		for (int i = 0; i < graph[1][top.x].size(); i++) {
			for (int j = 0; j < graph[2][top.y].size(); j++) {
				for (int k = 0; k < graph[3][top.z].size(); k++) {
					int nx = graph[1][top.x][i].first, ny = graph[2][top.y][j].first, nz = graph[3][top.z][k].first;
					long long next_weights = visited[top.x][top.y][top.z] + graph[1][top.x][i].second + graph[2][top.y][j].second + graph[3][top.z][k].second;
					
					if (visited[nx][ny][nz] > next_weights) {
						visited[nx][ny][nz] = next_weights;
						update(change_value(info(nx, ny, nz)), std::make_pair(next_weights, change_value(info(nx, ny, nz))));
					}
					cnt2++;
				}
			}
		}

		if (cnt1 >= f1 && cnt2 >= f2)
			break;
	}

	printf("%lld\n", visited[goals[1]][goals[2]][goals[3]]);
}