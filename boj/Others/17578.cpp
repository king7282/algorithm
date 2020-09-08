#include <stdio.h>
#include <algorithm>
#include <map>

char input[52][52], str[1010];
std::map<char, std::pair<int, int> > map;

int aabs(int num) {
	if (num < 0)
		return num * -1;
	return num;
}

int main(void) {
	while (1) {
		int n, m;
		scanf("%d %d", &n, &m);

		if (n == 0 && m == 0)
			break;
		map.clear();

		for (int i = 1; i <= n; i++) {
			getchar();
			for (int j = 1; j <= m; j++) {
				scanf("%c", &input[i][j]);
				map[input[i][j]] = std::make_pair(i, j);
			}
		}
		getchar();
		scanf("%s", str);
		int result = 0;
		std::pair<int, int> cur = std::make_pair(1, 1);
		for (int i = 0; str[i] != NULL; i++) {
			std::pair<int, int> next = map[str[i]];

			result += aabs(cur.first - next.first) + aabs(cur.second - next.second) + 1;
			cur = next;
		}

		printf("%d\n", result);
	}
}