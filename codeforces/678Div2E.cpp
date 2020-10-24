#include <stdio.h>
#include <algorithm>
#include <vector>
 
struct info {
	int x, y, index;
	info(int x, int y, int index) : x(x), y(y), index(index) {}
};
 
int input[100010], result[1000010], pq = 400, sum[400010], b[400010];
std::vector<int> index[100010];
std::vector<info> qu;
 
void update(int num) {
	sum[num]++;
	if (sum[num] == 1)
		b[num / pq]++;
}
 
void remove(int num) {
	sum[num]--;
	if (sum[num] == 0)
		b[num / pq]--;
}
 
int main(void) {
	int n, max1 = 0;
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", input + i);
		input[i]--;
		index[input[i]].push_back(i);
		max1 = std::max(max1, input[i]);
	}
 
	max1++;
	int cnt = 0;
	for (int i = 0; i <= max1; i++) {
		int prev = 1;
 
		for (int j = 0; j < index[i].size(); j++) {
			if (prev < index[i][j])
				qu.push_back(info(prev, index[i][j] - 1, cnt++));
			prev = index[i][j] + 1;
		}
 
		if (prev <= n)
			qu.push_back(info(prev, n, cnt++));
	}
 
	std::sort(qu.begin(), qu.end(), [](info a, info b) {
		if (a.x / pq == b.x / pq)
			return a.y < b.y;
		return a.x / pq < b.x / pq;
	});
 
	for (int i = qu[0].x; i <= qu[0].y; i++) {
		update(input[i]);
	}
 
	for (int i = 0; i <= max1 / pq; i++) {
		if (b[i] != pq) {
			for (int j = i * pq; j < (i + 1) * pq; j++) {
				if (sum[j] == 0) {
					result[qu[0].index] = j;
					break;
				}
			}
			break;
		}
	}
 
	for (int i = 1; i < qu.size(); i++) {
		if (qu[i - 1].y < qu[i].y) {
			for (int j = qu[i - 1].y + 1; j <= qu[i].y; j++) {
				update(input[j]);
			}
		}
		else {
			for (int j = qu[i - 1].y; j > qu[i].y; j--) {
				remove(input[j]);
			}
		}
 
		if (qu[i - 1].x < qu[i].x) {
			for (int j = qu[i - 1].x; j < qu[i].x; j++) {
				remove(input[j]);
			}
		}
		else {
			for (int j = qu[i].x; j < qu[i - 1].x; j++) {
				update(input[j]);
			}
		}
 
		for (int j = 0; j <= max1 / pq; j++) {
			if (b[j] != pq) {
				for (int k = j * pq; k < (j + 1) * pq; k++) {
					if (sum[k] == 0) {
						result[qu[i].index] = k;
						break;
					}
				}
				break;
			}
		}
	}
	
	int r = max1 + 1;
	cnt = 0;
	for (int i = 0; i <= max1; i++) {
		int prev = 1, v = -1;
 
		for (int j = 0; j < index[i].size(); j++) {
			if (prev < index[i][j]) {
				v = std::max(v, result[cnt]);
				cnt++;
			}
			prev = index[i][j] + 1;
		}
 
		if (prev <= n) {
			v = std::max(v, result[cnt]);
			cnt++;
		}
 
		if (v != i) {
			r = i;
			break;
		}
	}
 
	printf("%d\n", r + 1);
}