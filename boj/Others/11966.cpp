#include <stdio.h>

int main(void) {
	int a;
	scanf("%d", &a);

	bool result = true;

	while (a > 1 && result) {
		if (a % 2 == 1)
			result = false;
		a /= 2;
	}

	if (result)
		printf("1\n");
	else
		printf("0\n");
}