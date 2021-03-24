#include <stdio.h>

int main(void) {
	int e, s, m;
	scanf("%d %d %d", &e, &s, &m);
	int result = 1;

	while (1) {
		if (e == 1 && s == 1 && m == 1)
			break;

		e--;
		s--;
		m--;

		if (e == 0)
			e = 15;
		if (s == 0)
			s = 28;
		if (m == 0)
			m = 19;

		result++;
	}

	printf("%d\n", result);
}