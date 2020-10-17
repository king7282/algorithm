#include <stdio.h>
 
char input[300010];
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		getchar();
 
		bool right = true, left = true;
		
		for (int i = 0; i < n; i++) {
			scanf("%c", input + i);
			if (input[i] == '>')
				left = false;
			if (input[i] == '<')
				right = false;
		}
 
		int result = 0;
		for (int i = 0; i < n; i++) {
			int r = i, l = (i - 1 + n) % n;
			if (input[l] == '-' || input[r] == '-') {
				result++;
			}
			else if (input[l] == '>' && input[r] == '>') {
				if (right)
					result++;
			}
			else if (input[l] == '<' && input[r] == '<') {
				if (left)
					result++;
			}
		}
 
		printf("%d\n", result);
	}
}