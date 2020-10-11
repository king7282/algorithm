#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define SIZE 262144
 
int tree[SIZE * 2 + 1];
char input[200010];
std::vector<int> v;
 
void update(int num, int val) {
	num |= SIZE;
	tree[num] = val;
 
	while (num >>= 1)
		tree[num] = std::max(tree[num << 1], tree[num << 1 | 1]);
}
 
int query(int s, int e) {
	s |= SIZE, e |= SIZE;
	
	int r = 0;
 
	while (s <= e) {
		if (s % 2 == 1) r = std::max(tree[s], r);
		if (e % 2 == 0) r = std::max(tree[e], r);
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
 
	return r;
}
 
int main(void) {
	int test;
	scanf("%d", &test);
 
	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);
		getchar();
		v.clear();
		memset(tree, 0, sizeof(tree));
 
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%c", input + i);
			if (i != 1 && input[i] != input[i - 1]) {
				update(v.size(), cnt);
				v.push_back(cnt);
				cnt = 0;
			}
			cnt++;
		}
 
		update(v.size(), cnt);
		v.push_back(cnt);
		int result = 0;
 
		for (int i = 0; i < v.size(); i++) {
			if (v[i] == 0)
				continue;
 
			result++;
			if(v[i] == 1) {
				int s = i + 1, e = v.size() - 1, r = v.size();
 
				while (s <= e) {
					int mid = (s + e) / 2;
 
					if (query(i + 1, mid) > 1) {
						e = mid - 1;
						r = std::min(r, mid);
					}
					else
						s = mid + 1;
				}
 
				if (r == v.size()) {
					r = std::min((int)v.size() - 1, i + 1);
				}
 
				v[r]--;
				update(r, v[r]);
			}
		}
 
		printf("%d\n", result);
	}
}