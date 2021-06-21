#include <stdio.h>
#include <algorithm>
#include <set>

std::multiset<int> set;
int main(void) {
	int n, sum = 0;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		sum += a;
		if(a != 0)
			set.insert(a);
	}

	if (sum % 3 != 0) {
		printf("NO\n");
	}
	else {
		bool result = true;
		while (set.size() > 0) {
			int front = *set.begin();
			if (front >= 3)
				break;
			set.erase(set.begin());
			int end = *std::prev(set.end());
			set.erase(std::prev(set.end()));
			if (front == 1) {
				end -= 2;
			}
			else {
				end -= 1;
			}

			if (end < 0) {
				result = false;
				break;
			}

			if(end != 0)
				set.insert(end);
		}

		if (result)
			printf("YES\n");
		else
			printf("NO\n");
	}
}