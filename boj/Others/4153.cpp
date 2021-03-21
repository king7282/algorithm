#include <stdio.h>
#include <algorithm>

int A[3];

int main(void) {
	while (1) {
		scanf("%d %d %d", A, A + 1, A + 2);
		if (A[0] == 0 && A[1] == 0 && A[2] == 0)
			break;

		std::sort(A, A + 3);

		if (A[0] * A[0] + A[1] * A[1] == A[2] * A[2])
			printf("right\n");
		else
			printf("wrong\n");
	}

}