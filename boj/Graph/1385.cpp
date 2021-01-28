#include <stdio.h>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <vector>

std::map<std::pair<short, short>, std::pair<short, short>> prev;
std::set<std::pair<short, short>> check;
std::map<std::pair<short, short>, int> map;
int mov[6][2] = { {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}, {1, 0} };

short aabs(short num) {
	if (num < 0)
		return -1 * num;
	return num;
}

int main(void) {
	int start_num, end_num;
	std::pair<short, short> s, e;

	scanf("%d %d", &start_num, &end_num);
	if (start_num == end_num) {
		printf("%d\n", start_num);
		return 0;
	}

	map[{0, 0}] = 1;
	map[{0, 1}] = 2;
	map[{-1, 1}] = 3;
	map[{-1, 0}] = 4;
	map[{0, -1}] = 5;
	map[{1, -1}] = 6;

	std::pair<short, short> cur = std::make_pair(1, -1);
	
	int hap = 2, cnt = 7, d = 0;

	while (cnt <= 1000000) {
		if (d == 1) {
			for (int i = 1; i <= hap - 1 && cnt <= 1000000; i++) {
				cur.first += mov[d][0], cur.second += mov[d][1];

				if (start_num == cnt)
					s = cur;
				if (end_num == cnt)
					e = cur;
				map[cur] = cnt++;
			}
		}
		else {
			for (int i = 1; i <= hap && cnt <= 1000000; i++) {
				cur.first += mov[d][0], cur.second += mov[d][1];

				if (start_num == cnt)
					s = cur;
				if (end_num == cnt)
					e = cur;
				map[cur] = cnt++;
			}
		}

		d = (d + 1) % 6;
		if (d == 0)
			hap++;
	}

	std::queue<std::pair<short, short>> qu;
	qu.push(s);
	bool flag = false;

	while (!qu.empty() && !flag) {
		std::pair<short, short> front = qu.front();
		qu.pop();

		for (int i = 0; i < 6 && !flag; i++) {
			std::pair<short, short> next = front;
			next.first += mov[i][0];
			next.second += mov[i][1];

			if (map.find(next) == map.end() || check.find(next) != check.end())
				continue;

			if (aabs(next.first - e.first) + aabs(next.second - e.second) > aabs(front.first - e.first) + aabs(front.second - e.second))
				continue;

			check.insert(next);
			prev[next] = front;
			if (next == e)
				flag = true;
			qu.push(next);
		}
	}

	check.clear();
	while (!qu.empty())
		qu.pop();
	
	std::vector<int> result;
	cur = e;

	while (cur != s) {
		result.push_back(map[cur]);
		cur = prev[cur];
	}

	result.push_back(map[cur]);

	for (int i = result.size() - 1; i >= 0; i--)
		printf("%d ", result[i]);
	printf("\n");

}