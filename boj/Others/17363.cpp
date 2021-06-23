#include <stdio.h>

char map[110][110];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char input;
			scanf(" %c", &input);

			map[m - j + 1][i] = input;
		}
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			switch (map[i][j]) {
			case '-':
				map[i][j] = '|';
				break;
			case '|':
				map[i][j] = '-';
				break;
			case '/':
				map[i][j] = '\\';
				break;
			case '\\':
				map[i][j] = '/';
				break;
			case '^':
				map[i][j] = '<';
				break;
			case '<':
				map[i][j] = 'v';
				break;
			case 'v':
				map[i][j] = '>';
				break;
			case '>':
				map[i][j] = '^';
				break;

			}

			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}