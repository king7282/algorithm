#include <stdio.h>
#include <algorithm>

int main(void) {
	int l, a, b, c, d;
	scanf("%d %d %d %d %d", &l, &a, &b, &c, &d);

	int korean = a / c, math = b / d;
	if (a % c != 0)
		korean++;
	if (b % d != 0)
		math++;

	printf("%d\n", l - std::max(korean, math));
}