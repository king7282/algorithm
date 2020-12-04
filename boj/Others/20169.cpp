#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>

struct point {
	int x, y, type; // type[0 : right, 1 : up, 2 : left, 3 : down, 4 : intersection]
	int left, right, up, down;

	point(int x, int y, int type) : x(x), y(y), type(type) {}
};

struct info {
	int x, y, index;
	info(int x, int y, int index) : x(x), y(y), index(index) {}
};

bool operator<(info a, info b) {
	if (a.x == b.x) {
		if (a.y == b.y)
			return a.index < b.index;
		return a.y < b.y;
	}
	return a.x < b.x;
}
bool check[300010][4];
std::vector<point> p;
std::pair<std::pair<int, int>, std::pair<int, int>> input[510];
std::vector<info> X, Y;
int mov[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int main(void) {
	int n, t;
	scanf("%d %d", &n, &t);
	int start = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &input[i].first.first, &input[i].first.second, &input[i].second.first, &input[i].second.second);

		if (input[i].first.first == input[i].second.first) {
			X.push_back(info(input[i].first.first, std::min(input[i].first.second, input[i].second.second), p.size()));
			Y.push_back(info(std::min(input[i].first.second, input[i].second.second), input[i].first.first, p.size()));
			p.push_back(point(input[i].first.first, std::min(input[i].first.second, input[i].second.second), 1));

			X.push_back(info(input[i].first.first, std::max(input[i].first.second, input[i].second.second), p.size()));
			Y.push_back(info(std::max(input[i].first.second, input[i].second.second), input[i].first.first, p.size()));
			p.push_back(point(input[i].first.first, std::max(input[i].first.second, input[i].second.second), 3));

			if (i == 0) {
				if (input[i].first.second < input[i].second.second) {
					start = 0;
				}
				else
					start = 1;
			}

		}
		else {
			Y.push_back(info(input[i].first.second, std::min(input[i].first.first, input[i].second.first), p.size()));
			X.push_back(info(std::min(input[i].first.first, input[i].second.first), input[i].first.second, p.size()));
			p.push_back(point(std::min(input[i].first.first, input[i].second.first), input[i].first.second, 0));

			Y.push_back(info(input[i].first.second, std::max(input[i].first.first, input[i].second.first), p.size()));
			X.push_back(info(std::max(input[i].first.first, input[i].second.first), input[i].first.second, p.size()));
			p.push_back(point(std::max(input[i].first.first, input[i].second.first), input[i].first.second, 2));

			if (i == 0) {
				if (input[i].first.first < input[i].second.first) {
					start = 0;
				}
				else
					start = 1;
			}
		}

		for (int j = 0; j < i; j++) {
			if (input[i].first.first == input[i].second.first) {
				if (input[j].first.second == input[j].second.second) {
					if (std::min(input[i].first.second, input[i].second.second) <= input[j].first.second && input[j].first.second <= std::max(input[i].first.second, input[i].second.second)) {
						if (std::min(input[j].first.first, input[j].second.first) <= input[i].first.first && input[i].first.first <= std::max(input[j].first.first, input[j].second.first)) {
							X.push_back(info(input[i].first.first, input[j].first.second, p.size()));
							Y.push_back(info(input[j].first.second, input[i].first.first, p.size()));
							p.push_back(point(input[i].first.first, input[j].first.second, 4));
						}
					}
				}
			}
			else {
				if (input[j].first.first == input[j].second.first) {
					if (std::min(input[i].first.first, input[i].second.first) <= input[j].first.first && input[j].first.first <= std::max(input[i].first.first, input[i].second.first)) {
						if (std::min(input[j].first.second, input[j].second.second) <= input[i].first.second && input[i].first.second <= std::max(input[j].first.second, input[j].second.second)) {
							X.push_back(info(input[j].first.first, input[i].first.second, p.size()));
							Y.push_back(info(input[i].first.second, input[j].first.first, p.size()));
							p.push_back(point(input[j].first.first, input[i].first.second, 4));
						}
					}
				}
			}
		}
	}

	std::sort(X.begin(), X.end());
	std::sort(Y.begin(), Y.end());

	for (int i = 0; i < p.size(); i++) {
		if (p[i].type == 0 || p[i].type == 4) {
			int index = std::lower_bound(Y.begin(), Y.end(), info(p[i].y, p[i].x, i)) - Y.begin() + 1;
			p[i].right = Y[index].index;
		}
		if (p[i].type == 1 || p[i].type == 4) {
			int index = std::lower_bound(X.begin(), X.end(), info(p[i].x, p[i].y, i)) - X.begin() + 1;
			p[i].up = X[index].index;
		}
		if (p[i].type == 2 || p[i].type == 4) {
			int index = std::lower_bound(Y.begin(), Y.end(), info(p[i].y, p[i].x, i)) - Y.begin() - 1;
			p[i].left = Y[index].index;
		}
		if (p[i].type == 3 || p[i].type == 4) {
			int index = std::lower_bound(X.begin(), X.end(), info(p[i].x, p[i].y, i)) - X.begin() - 1;
			p[i].down = X[index].index;
		}
	}
	
	bool finish = false;
	std::pair<int, int> result = std::make_pair(0, 0);
	int cur = start, d = p[start].type, tt = 0;
	int start_d = d;

	while (1) {
		int next_tt = 0, next = 0;
		if (check[cur][d] == true) {
			t -= tt;
			start = cur;
			start_d = d;
			break;
		}
		check[cur][d] = true;

		if (d == 0) {
			next = p[cur].right;
			next_tt = p[next].x - p[cur].x;
		}
		else if (d == 1) {
			next = p[cur].up;
			next_tt = p[next].y - p[cur].y;
		}
		else if (d == 2) {
			next = p[cur].left;
			next_tt = p[cur].x - p[next].x;
		}
		else {
			next = p[cur].down;
			next_tt = p[cur].y - p[next].y;
		}

		if (tt <= t && t <= tt + next_tt) {
			result.first = p[cur].x + mov[d][0] * (t - tt);
			result.second = p[cur].y + mov[d][1] * (t - tt);
			finish = true;
			break;
		}

		tt += next_tt;
		cur = next;
		if (p[cur].type == 4)
			d = (d + 1) % 4;
		else
			d = (d + 2) % 4;
	}

	if (finish) {
		printf("%d %d\n", result.first, result.second);
		return 0;
	}
	
	cur = start, d = start_d, tt = 0;
	memset(check, false, sizeof(check));

	while (1) {
		int next_tt = 0, next = 0;
		if (check[cur][d] == true) {
			t %= tt;
			start = cur;
			start_d = d;
			break;
		}
		check[cur][d] = true;

		if (d == 0) {
			next = p[cur].right;
			next_tt = p[next].x - p[cur].x;
		}
		else if (d == 1) {
			next = p[cur].up;
			next_tt = p[next].y - p[cur].y;
		}
		else if (d == 2) {
			next = p[cur].left;
			next_tt = p[cur].x - p[next].x;
		}
		else {
			next = p[cur].down;
			next_tt = p[cur].y - p[next].y;
		}

		if (tt <= t && t <= tt + next_tt) {
			result.first = p[cur].x + mov[d][0] * (t - tt);
			result.second = p[cur].y + mov[d][1] * (t - tt);
			finish = true;
			break;
		}

		tt += next_tt;
		cur = next;
		if (p[cur].type == 4)
			d = (d + 1) % 4;
		else
			d = (d + 2) % 4;
	}

	if (finish) {
		printf("%d %d\n", result.first, result.second);
		return 0;
	}

	cur = start, d = start_d, tt = 0;
	memset(check, false, sizeof(check));
	while (1) {
		int next_tt = 0, next = 0;
		if (check[cur][d] == true) {
			t %= tt;
			start = cur;
			start_d = d;
			break;
		}
		check[cur][d] = true;

		if (d == 0) {
			next = p[cur].right;
			next_tt = p[next].x - p[cur].x;
		}
		else if (d == 1) {
			next = p[cur].up;
			next_tt = p[next].y - p[cur].y;
		}
		else if (d == 2) {
			next = p[cur].left;
			next_tt = p[cur].x - p[next].x;
		}
		else {
			next = p[cur].down;
			next_tt = p[cur].y - p[next].y;
		}

		if (tt <= t && t <= tt + next_tt) {
			result.first = p[cur].x + mov[d][0] * (t - tt);
			result.second = p[cur].y + mov[d][1] * (t - tt);
			finish = true;
			break;
		}

		tt += next_tt;
		cur = next;
		if (p[cur].type == 4)
			d = (d + 1) % 4;
		else
			d = (d + 2) % 4;
	}

	if (finish) {
		printf("%d %d\n", result.first, result.second);
		return 0;
	}
	assert(false);
}