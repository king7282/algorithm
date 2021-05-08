#include <stdio.h>
#include <algorithm>

int main(void) {
	long long x, y;
	scanf("%lld %lld", &x, &y);
	if (x == y) {
		printf("-1\n");
		return 0;
	}

	long long s = 1, e = x, r = x + 1;

	while (s <= e) {
		long long mid = (s + e) / 2;

		if (y * 100 / x < (y + mid) * 100 / (x + mid)) {
			e = mid - 1;
			r = std::min(r, mid);
		}
		else
			s = mid + 1;
	}
    
    if(r == x + 1) {
        printf("-1\n");
    }
    else
	    printf("%lld\n", r);
}