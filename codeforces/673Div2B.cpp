#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
 
bool check[100010];
int input[100010];
std::vector<int> X;
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n, T, cnt = 0;
		scanf("%d %d", &n, &T);
		X.clear();
 
		for (int i = 1; i <= n; i++) {
			scanf("%d", input + i);
			if (T % 2 == 0 && input[i] == T / 2)
				cnt++;
			X.push_back(input[i]);
			check[i] = false;
		}
 
		std::sort(X.begin(), X.end());
		X.erase(std::unique(X.begin(), X.end()), X.end());
 
		for (int i = 0; i < X.size() && X[i] <= T / 2; i++) {
			if (T % 2 == 0 && T / 2 == X[i])
				continue;
 
			int upper = std::lower_bound(X.begin(), X.end(), T - X[i]) - X.begin();
 
			if (X.size() == upper || X[upper] != T - X[i])
				continue;
 
			check[upper] = true;
		}
 
		int cnt2 = 0;
		for (int i = 1; i <= n; i++) {
			if (T % 2 == 0 && input[i] == T / 2) {
				if (cnt2 < cnt / 2)
					printf("0 ");
				else
					printf("1 ");
				cnt2++;
			}
			else {
				int index = std::lower_bound(X.begin(), X.end(), input[i]) - X.begin();
				if (check[index] == false)
					printf("0 ");
				else
					printf("1 ");
			}
		}
		printf("\n");
	}
 }