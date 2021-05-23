#include <stdio.h>

char A[10010], B[10010];

int main(void) {
	scanf("%s %s", A, B);

	long long hapA = 0, hapB = 0;
	for (int i = 0; A[i] != NULL; i++) {
		hapA += A[i] - '0';
	}

	for (int i = 0; B[i] != NULL; i++) {
		hapB += B[i] - '0';
	}

	printf("%lld\n", hapA * hapB);
}