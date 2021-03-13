#include <stdio.h>

int get_input(void) {
	int result = 0;
	while (1) {
		char c = getchar();
		if (c == ' ' || c == '\n')
			break;
		result = result * 10 + (c - '0');
	}

	return result;
}

int main(void) {
	int test = get_input();

	for (int t = 0; t < test; t++) {
		int a = get_input(), b = get_input();
		printf("%d\n", a + b);
	}
}