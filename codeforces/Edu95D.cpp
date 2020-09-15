#include <stdio.h>
#include <set>
#include <algorithm>
#include <vector>
 
std::set<int> number;
std::multiset<int> gap;
std::vector<int> result;
 
int main(void) {
	int n, q;
	scanf("%d %d", &n, &q);
 
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		number.insert(a);
	}
 
	int prev = *(number.begin());
	for (auto it = number.begin(); it != number.end(); it++) {
		if (*it - prev != 0)
			gap.insert(*it - prev);
		prev = *it;
	}
 
	if (n <= 2)
		result.push_back(0);
	else
		result.push_back(*std::prev(number.end()) - *(number.begin()) - *std::prev(gap.end()));
 
	for (int i = 1; i <= q; i++) {
		int x, a;
		scanf("%d %d", &x, &a);
 
		if (x == 1) {
			number.insert(a);
			if (number.size() > 1) {
				auto it = number.lower_bound(a);
				if (it == number.begin()) {
					gap.insert(*std::next(it) - *it);
				}
				else if (std::next(it) == number.end()) {
					gap.insert(*it - *std::prev(it));
				}
				else {
					gap.erase(gap.find(*std::next(it) - *std::prev(it)));
					gap.insert(*std::next(it) - *it);
					gap.insert(*it - *std::prev(it));
				}
			}
		}
		else {
			auto it = number.find(a);
 
			if (number.size() > 1) {
				if (it == number.begin()) {
					gap.erase(gap.find(*std::next(it) - *it));
				}
				else if (std::next(it) == number.end()) {
					gap.erase(gap.find(*it - *std::prev(it)));
				}
				else {
					gap.erase(gap.find(*std::next(it) - *it));
					gap.erase(gap.find(*it - *std::prev(it)));
					gap.insert(*std::next(it) - *std::prev(it));
				}
			}
 
			number.erase(it);
		}
 
		if (number.size() <= 2)
			result.push_back(0);
		else
			result.push_back(*std::prev(number.end()) - *(number.begin()) - *std::prev(gap.end()));
	}
 
	for (int i = 0; i < result.size(); i++)
		printf("%d\n", result[i]);
}