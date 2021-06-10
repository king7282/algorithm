#include <stdio.h>

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		double input;
		scanf("%lf", &input);
		char c;
		while (1) {
			c = getchar();
			if (c == ' ')
				continue;
			else if (c == '\n' || c == EOF)
				break;
			else if (c == '@')
				input *= 3;
			else if (c == '%')
				input += 5;
			else
				input -= 7;
		}

		printf("%.2lf\n", input);
	}
}