#include <stdio.h>
#include <algorithm>
#include <vector>
 
std::vector<int> v;
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		v.clear();
 
		for (int i = 4 * n; i >= 2; i -= 2) {
			bool flag = true;
			for (int j = 0; j < v.size() && flag; j++) {
				if (i % v[j] == 0 || v[j] % i == 0)
					flag = false;
			}
 
			if (flag && v.size() < n)
				v.push_back(i);
		}
 
		for (int i = 0; i < v.size(); i++)
			printf("%d ", v[i]);
		printf("\n");
	}
}