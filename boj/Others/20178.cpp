#include <stdio.h>
#include <algorithm>

int input[510][510], result[510][510];
int n;

void remove(int i, int j) {
	for (int k = 1; k <= n; k++) {
		input[j][k] ^= input[i][k];
		result[j][k] ^= result[i][k];
	}
}

void change(int i, int j) {
	for (int k = 1; k <= n; k++) {
		std::swap(input[i][k], input[j][k]);
		std::swap(result[i][k], result[j][k]);
	}
}

int main(void) {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &input[j][i]);
		}
		result[i][i] = 1;
	}

	bool flag = true;

	for (int i = 1; i <= n; i++) {
		int index = -1;
		for (int j = i; j <= n; j++) {
			if (input[j][i] == 1) {
				index = j;
				break;
			}
		}

		if (index == -1) {
			flag = false;
			break;
		}
		change(i, index);

		for (int j = i + 1; j <= n; j++) {
			if (input[j][i] == 1) {
				remove(i, j);
			}
		}
	}

	for (int i = n; i >= 1; i--) {
		if (input[i][i] == 0) {
			flag = false;
			break;
		}

		for (int j = i - 1; j >= 1; j--) {
			if (input[j][i] == 1)
				remove(i, j);
		}
	}

	if (flag) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (result[j][i] == 1) {
					printf("%d ", j);
				}
			}
			printf("\n");
		}
	}
	else {
		printf("-1\n");
	}
}