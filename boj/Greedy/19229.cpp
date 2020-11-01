#include <stdio.h>
#include <algorithm>
#include <cstring>

char input[1000010];
char result[1010][1010];

int main(void) {
	int n, l, k;
	scanf("%d %d %d", &n, &l, &k);
	getchar();

	for (int i = 1; i <= n * l; i++)
		scanf("%c", input + i);

	std::sort(input + 1, input + 1 + n * l);

	memset(result, -1, sizeof(result));
	
	int index = 1, start = 1;
	for (int i = 1; i <= l; i++) {
		for (int j = start; j < k; j++) {
			result[j][i] = input[index++];
		}
		result[k][i] = input[index++];
		while (start < k && result[start][i] != result[k][i]) {
			start++;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= l; j++) {
			if (result[i][j] == -1)
				result[i][j] = input[index++];
			printf("%c", result[i][j]);
		}
		printf("\n");
	}
}