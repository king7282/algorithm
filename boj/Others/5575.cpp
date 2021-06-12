#include <stdio.h>

int main(void) {
	for (int t = 0; t < 3; t++) {
		int sh, sm, ss, eh, em, es;
		scanf("%d %d %d %d %d %d", &sh, &sm, &ss, &eh, &em, &es);

		int s = sh * 3600 + sm * 60 + ss, e = eh * 3600 + em * 60 + es;
		int result = e - s;

		printf("%d %d %d\n", result / 3600, (result % 3600) / 60, result % 60);
		
	}
}