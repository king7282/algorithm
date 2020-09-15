#include <stdio.h>
#include <algorithm>
#include <vector>
 
int input[110], check[110];
std::vector<int> X;
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		X.clear();
 
		for (int i = 1; i <= n; i++)
			scanf("%d", input + i);
 
		for (int i = 1; i <= n; i++) {
			scanf("%d", check + i);
			if (check[i] == 0)
				X.push_back(input[i]);
		}
 
		std::sort(X.rbegin(), X.rend());
		int index = 0;
		for (int i = 1; i <= n; i++) {
			if (check[i] == 0)
				input[i] = X[index++];
		}
 
		for (int i = 1; i <= n; i++)
			printf("%d ", input[i]);
		printf("\n");
		
	}
}