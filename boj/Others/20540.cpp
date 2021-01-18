#include <stdio.h>

char MBTI[4][2] = { {'E', 'I'}, {'S', 'N'}, {'T', 'F'}, {'J', 'P'} };

int main(void) {
	char input[4], result[4];

	for (int i = 0; i < 4; i++) {
		scanf("%c", input + i);

		for (int j = 0; j < 2; j++) {
			if (input[i] == MBTI[i][j]) {
				result[i] = MBTI[i][(j + 1) % 2];
				break;
			}
		}
	}

	for (int i = 0; i < 4; i++)
		printf("%c", result[i]);
	printf("\n");
}