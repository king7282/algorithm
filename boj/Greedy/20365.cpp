#include <stdio.h>
#include <algorithm>

char input[500010];

int main(void) {
	int n;
	scanf("%d", &n);
	getchar();

	for (int i = 1; i <= n; i++)
		scanf("%c", input + i);

	int blue = 0, red = 0;

	for (int i = 1; i <= n; i++) {
		if (input[i] != input[i - 1]) {
			if (input[i] == 'B')
				blue++;
			else
				red++;
		}
	}

	printf("%d\n", std::min(blue, red) + 1);
}